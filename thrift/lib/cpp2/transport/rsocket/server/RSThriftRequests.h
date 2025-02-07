/*
 * Copyright 2017-present Facebook, Inc.
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

#pragma once

#include <rsocket/Payload.h>
#include <thrift/lib/cpp2/transport/core/ThriftRequest.h>
#include <yarpl/flowable/Subscriber.h>
#include <yarpl/single/SingleObserver.h>

namespace apache {
namespace thrift {

namespace detail {
std::unique_ptr<folly::IOBuf> serializeMetadata(
    const ResponseRpcMetadata& responseMetadata);

// Deserializes metadata returning an invalid object with the kind field unset
// on error.
bool deserializeMetadata(
    const folly::IOBuf& buffer,
    RequestRpcMetadata& metadata);
} // namespace detail

class RSOneWayRequest final : public ThriftRequestCore {
 public:
  RSOneWayRequest(
      server::ServerConfigs& serverConfigs,
      RequestRpcMetadata&& metadata,
      std::shared_ptr<Cpp2ConnContext> connContext,
      folly::EventBase* evb,
      folly::Function<void(RSOneWayRequest*)> onDestroy);

  virtual ~RSOneWayRequest();

  void cancel() override;

  void sendThriftResponse(
      ResponseRpcMetadata&&,
      std::unique_ptr<folly::IOBuf>) noexcept override;

  void sendStreamThriftResponse(
      ResponseRpcMetadata&&,
      std::unique_ptr<folly::IOBuf>,
      apache::thrift::SemiStream<
          std::unique_ptr<folly::IOBuf>>) noexcept override;

  folly::EventBase* getEventBase() noexcept override;

 private:
  folly::EventBase* evb_;
  folly::Function<void(RSOneWayRequest*)> onDestroy_;
  std::shared_ptr<Cpp2ConnContext> connContext_;
};

class RSSingleRequest final : public ThriftRequestCore {
 public:
  RSSingleRequest(
      server::ServerConfigs& serverConfigs,
      RequestRpcMetadata&& metadata,
      std::shared_ptr<Cpp2ConnContext> connContext,
      folly::EventBase* evb,
      std::shared_ptr<yarpl::single::SingleObserver<rsocket::Payload>>
          singleObserver);

  void sendThriftResponse(
      ResponseRpcMetadata&&,
      std::unique_ptr<folly::IOBuf>) noexcept override;

  void sendStreamThriftResponse(
      ResponseRpcMetadata&&,
      std::unique_ptr<folly::IOBuf>,
      apache::thrift::SemiStream<
          std::unique_ptr<folly::IOBuf>>) noexcept override;

  folly::EventBase* getEventBase() noexcept override;

  bool isReplyChecksumNeeded() const override {
    return true;
  }

 private:
  folly::EventBase* evb_;
  std::shared_ptr<yarpl::single::SingleObserver<rsocket::Payload>>
      singleObserver_;
  std::shared_ptr<Cpp2ConnContext> connContext_;
};

class RSStreamRequest final : public ThriftRequestCore {
 public:
  RSStreamRequest(
      server::ServerConfigs& serverConfigs,
      RequestRpcMetadata&& metadata,
      std::shared_ptr<Cpp2ConnContext> connContext,
      folly::EventBase* evb,
      std::shared_ptr<yarpl::flowable::Subscriber<rsocket::Payload>>
          subscriber);

  bool isStream() const override {
    return true;
  }

  void sendThriftResponse(
      ResponseRpcMetadata&& metadata,
      std::unique_ptr<folly::IOBuf> response) noexcept override;

  void sendStreamThriftResponse(
      ResponseRpcMetadata&& metadata,
      std::unique_ptr<folly::IOBuf> response,
      apache::thrift::SemiStream<std::unique_ptr<folly::IOBuf>>
          stream) noexcept override;

  folly::EventBase* getEventBase() noexcept override;

  bool isReplyChecksumNeeded() const override {
    return true;
  }

 protected:
  folly::EventBase* evb_;
  std::shared_ptr<yarpl::flowable::Subscriber<rsocket::Payload>> subscriber_;
  std::shared_ptr<Cpp2ConnContext> connContext_;
};

} // namespace thrift
} // namespace apache
