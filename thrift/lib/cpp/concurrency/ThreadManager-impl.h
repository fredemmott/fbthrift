/*
 * Copyright 2014-present Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef THREADMANAGERIMPL_H
#define THREADMANAGERIMPL_H

#include <deque>
#include <memory>

#include <folly/DefaultKeepAliveExecutor.h>
#include <folly/PriorityMPMCQueue.h>
#include <folly/ThreadLocal.h>
#include <folly/concurrency/PriorityUnboundedQueueSet.h>
#include <folly/executors/Codel.h>
#include <folly/io/async/Request.h>
#include <folly/synchronization/LifoSem.h>
#include <folly/synchronization/SmallLocks.h>
#include <thrift/lib/cpp/concurrency/Monitor.h>

namespace apache { namespace thrift { namespace concurrency {

using std::shared_ptr;
using std::make_shared;
using folly::Codel;
using std::dynamic_pointer_cast;
using std::unique_ptr;

class ThreadManager::Task {
 public:
  enum STATE {
    WAITING,
    EXECUTING,
    CANCELLED,
    COMPLETE
  };

  Task(shared_ptr<Runnable> runnable,
       const std::chrono::milliseconds& expiration)
    : runnable_(std::move(runnable))
    , queueBeginTime_(SystemClock::now())
    , expireTime_(expiration > std::chrono::milliseconds::zero() ?
                  queueBeginTime_ + expiration : SystemClockTimePoint())
    , context_(folly::RequestContext::saveContext()) {}

  ~Task() {}

  void run() {
    folly::RequestContextScopeGuard rctx(context_);
    runnable_->run();
  }

  const shared_ptr<Runnable>& getRunnable() const {
    return runnable_;
  }

  SystemClockTimePoint getExpireTime() const {
    return expireTime_;
  }

  SystemClockTimePoint getQueueBeginTime() const {
    return queueBeginTime_;
  }

  bool canExpire() const {
    return expireTime_ != SystemClockTimePoint();
  }

  bool statsEnabled() const {
    return queueBeginTime_ != SystemClockTimePoint();
  }

  const std::shared_ptr<folly::RequestContext>& getContext() const {
    return context_;
  }

 private:
  shared_ptr<Runnable> runnable_;
  SystemClockTimePoint queueBeginTime_;
  SystemClockTimePoint expireTime_;
  std::shared_ptr<folly::RequestContext> context_;
};

template <typename SemType>
class ThreadManager::ImplT : public ThreadManager,
                             public folly::DefaultKeepAliveExecutor {
  template <typename SemTypeT>
  class Worker;

 public:
  explicit ImplT(bool enableTaskStats = false, size_t numPriorities = 1)
      : workerCount_(0),
        intendedWorkerCount_(0),
        idleCount_(0),
        totalTaskCount_(0),
        expiredCount_(0),
        workersToStop_(0),
        enableTaskStats_(enableTaskStats),
        statsLock_{0},
        waitingTimeUs_(0),
        executingTimeUs_(0),
        numTasks_(0),
        state_(ThreadManager::UNINITIALIZED),
        tasks_(numPriorities),
        monitor_(&mutex_),
        deadWorkerMonitor_(&mutex_),
        deadWorkers_(),
        namePrefix_(""),
        namePrefixCounter_(0),
        codelEnabled_(false || FLAGS_codel_enabled) {}

  ~ImplT() override { stop(); }

  void start() override;

  void stop() override { stopImpl(false); }

  void join() override { stopImpl(true); }

  ThreadManager::STATE state() const override {
    return state_;
  }

  shared_ptr<ThreadFactory> threadFactory() const override {
    Guard g(mutex_);
    return threadFactory_;
  }

  void threadFactory(shared_ptr<ThreadFactory> value) override {
    Guard g(mutex_);
    threadFactory_ = value;
  }

  std::string getNamePrefix() const override {
    Guard g(mutex_);
    return namePrefix_;
  }

  void setNamePrefix(const std::string& name) override {
    Guard g(mutex_);
    namePrefix_ = name;
  }

  void addWorker(size_t value) override;

  void removeWorker(size_t value) override;

  size_t idleWorkerCount() const override {
    return idleCount_;
  }

  size_t workerCount() const override {
    return workerCount_;
  }

  size_t pendingTaskCount() const override {
    return tasks_.size();
  }

  size_t totalTaskCount() const override {
    return totalTaskCount_;
  }

  size_t expiredTaskCount() override {
    Guard g(mutex_);
    size_t result = expiredCount_;
    expiredCount_ = 0;
    return result;
  }

  bool canSleep();

  void add(
      shared_ptr<Runnable> value,
      int64_t timeout,
      int64_t expiration,
      bool cancellable,
      bool numa) noexcept override;

  /**
   * Implements folly::Executor::add()
   */
  void add(folly::Func f) override {
    add(FunctionRunner::create(std::move(f)), 0LL, 0LL, false, false);
  }

  void remove(shared_ptr<Runnable> task) override;

  shared_ptr<Runnable> removeNextPending() override;

  void clearPending() override;

  void setExpireCallback(ExpireCallback expireCallback) override;
  void setCodelCallback(ExpireCallback expireCallback) override;
  void setThreadInitCallback(InitCallback initCallback) override {
    initCallback_ = initCallback;
  }

  void getStats(std::chrono::microseconds& waitTime,
                std::chrono::microseconds& runTime,
                int64_t maxItems) override;
  void enableCodel(bool) override;
  Codel* getCodel() override;

  // Methods to be invoked by workers
  void workerStarted(Worker<SemType>* worker);
  void workerExiting(Worker<SemType>* worker);
  void reportTaskStats(const Task& task,
                       const SystemClockTimePoint& workBegin,
                       const SystemClockTimePoint& workEnd);
  std::unique_ptr<Task> waitOnTask();
  void onTaskExpired(const Task& task);

  Codel codel_;

 protected:
  void add(
      size_t priority,
      shared_ptr<Runnable> value,
      int64_t timeout,
      int64_t expiration,
      bool cancellable,
      bool numa) noexcept;

  // returns a string to attach to namePrefix when recording
  // stats
  virtual std::string statContext(const Task&) {
    return "";
  }

 private:
  void stopImpl(bool joinArg);
  void removeWorkerImpl(size_t value, bool afterTasks = false);
  bool shouldStop();

  size_t workerCount_;
  // intendedWorkerCount_ tracks the number of worker threads that we currently
  // want to have.  This may be different from workerCount_ while we are
  // attempting to remove workers:  While we are waiting for the workers to
  // exit, intendedWorkerCount_ will be smaller than workerCount_.
  size_t intendedWorkerCount_;
  std::atomic<size_t> idleCount_;
  std::atomic<size_t> totalTaskCount_;
  size_t expiredCount_;
  std::atomic<int> workersToStop_;

  const bool enableTaskStats_;
  folly::MicroSpinLock statsLock_;
  std::chrono::microseconds waitingTimeUs_;
  std::chrono::microseconds executingTimeUs_;
  int64_t numTasks_;

  ExpireCallback expireCallback_;
  ExpireCallback codelCallback_;
  InitCallback initCallback_;

  ThreadManager::STATE state_;
  shared_ptr<ThreadFactory> threadFactory_;

  folly::PriorityUMPMCQueueSet<std::unique_ptr<Task>, /* MayBlock = */ false>
      tasks_;

  Mutex mutex_;
  // monitor_ is signaled on any of the following events:
  // - a new task is added to the task queue
  // - state_ changes
  Monitor monitor_;
  SemType waitSem_;
  // deadWorkerMonitor_ is signaled whenever a worker thread exits
  Monitor deadWorkerMonitor_;
  std::deque<shared_ptr<Thread> > deadWorkers_;

  folly::ThreadLocal<bool> isThreadManagerThread_{
      [] { return new bool(false); }};
  std::string namePrefix_;
  uint32_t namePrefixCounter_;

  bool codelEnabled_;
};


}}}

#endif
