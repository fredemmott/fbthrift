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
#include <cstdint>
#include <functional>

#include <folly/Range.h>
#include <folly/SocketAddress.h>
#include <folly/Try.h>
#include <folly/executors/GlobalExecutor.h>
#include <folly/futures/Future.h>
#include <folly/futures/Promise.h>
#include <thrift/lib/cpp/async/TAsyncSocket.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>
#include <thrift/lib/cpp2/async/RequestChannel.h>

namespace thrift {
namespace py3 {
typedef std::unique_ptr<
    apache::thrift::RequestChannel,
    folly::DelayedDestruction::Destructor>
    RequestChannel_ptr;

typedef std::unique_ptr<
    apache::thrift::HeaderClientChannel,
    folly::DelayedDestruction::Destructor>
    HeaderChannel_ptr;

/*
 * T is the cpp2 async client class
 * U is the py3 clientwraper class
 */
template <class T, class U>
std::shared_ptr<U> makeClientWrapper(RequestChannel_ptr&& channel) {
  std::shared_ptr<apache::thrift::RequestChannel> channel_ = std::move(channel);
  auto client = std::make_shared<T>(channel_);
  return std::make_shared<U>(std::move(client), std::move(channel_));
}

void destroyInEventBaseThread(RequestChannel_ptr&& ptr) {
  auto eb = ptr->getEventBase();
  eb->runInEventBaseThread([ptr = std::move(ptr)] {});
}

HeaderChannel_ptr configureClientChannel(
    HeaderChannel_ptr&& chan,
    CLIENT_TYPE client,
    apache::thrift::protocol::PROTOCOL_TYPES proto) {
  chan->setProtocolId(proto);
  if (client != THRIFT_HEADER_CLIENT_TYPE) {
    chan->setClientType(client);
    chan->forceClientType(true);
  }

  if (client == THRIFT_FRAMED_DEPRECATED) {
    chan->setProtocolId(
        apache::thrift::protocol::PROTOCOL_TYPES::T_BINARY_PROTOCOL);
  } else if (client == THRIFT_FRAMED_COMPACT) {
    chan->setProtocolId(
        apache::thrift::protocol::PROTOCOL_TYPES::T_COMPACT_PROTOCOL);
  }
  return std::move(chan);
}

/**
 * Create a thrift channel by connecting to a host:port over TCP.
 */
folly::Future<RequestChannel_ptr> createThriftChannelTCP(
    std::string&& host,
    const uint16_t port,
    const uint32_t connect_timeout,
    CLIENT_TYPE client_t,
    apache::thrift::protocol::PROTOCOL_TYPES proto,
    std::string&& endpoint) {
  auto eb = folly::getEventBase();
  return folly::via(
      eb, [=, host{std::move(host)}, endpoint{std::move(endpoint)}] {
        auto chan = configureClientChannel(
            apache::thrift::HeaderClientChannel::newChannel(
                apache::thrift::async::TAsyncSocket::newSocket(
                    eb, host, port, connect_timeout)),
            client_t,
            proto);
        if (client_t == THRIFT_HTTP_CLIENT_TYPE) {
          chan->useAsHttpClient(host, endpoint);
        }
        return std::move(chan);
      });
}

/**
 * Create a thrift channel by connecting to a Unix domain socket.
 */
folly::Future<RequestChannel_ptr> createThriftChannelUnix(
    std::string&& path,
    const uint32_t connect_timeout,
    CLIENT_TYPE client_t,
    apache::thrift::protocol::PROTOCOL_TYPES proto) {
  auto eb = folly::getEventBase();
  return folly::via(eb, [=, path{std::move(path)}] {
    return configureClientChannel(
        apache::thrift::HeaderClientChannel::newChannel(
            apache::thrift::async::TAsyncSocket::newSocket(
                eb,
                folly::SocketAddress::makeFromPath(
                    folly::StringPiece(path.data(), path.size())),
                connect_timeout)),
        client_t,
        proto);
  });
}

} // namespace py3
} // namespace thrift
