/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#include <src/gen-py3/module/clients_wrapper.h>

namespace cpp2 {


RaiserClientWrapper::RaiserClientWrapper(
    std::shared_ptr<::cpp2::RaiserAsyncClient> async_client,
    std::shared_ptr<apache::thrift::RequestChannel> channel) : 
    async_client(async_client),
      channel_(channel) {}

RaiserClientWrapper::~RaiserClientWrapper() {}

folly::Future<folly::Unit> RaiserClientWrapper::disconnect() {
  return folly::via(
    this->async_client->getChannel()->getEventBase(),
    [cha = std::move(channel_), cli = std::move(async_client)] {});
}

void RaiserClientWrapper::setPersistentHeader(const std::string& key, const std::string& value) {
    auto headerChannel = async_client->getHeaderChannel();
    if (headerChannel != nullptr) {
        headerChannel->setPersistentHeader(key, value);
    }
}


folly::Future<folly::Unit>
RaiserClientWrapper::doBland(
    apache::thrift::RpcOptions& rpcOptions) {
  folly::Promise<folly::Unit> _promise;
  auto _future = _promise.getFuture();
  auto callback = std::make_unique<::thrift::py3::FutureCallback<folly::Unit>>(
    std::move(_promise), rpcOptions, async_client->recv_wrapped_doBland, channel_);
  async_client->doBland(
    rpcOptions,
    std::move(callback)
  );
  return _future;
}

folly::Future<folly::Unit>
RaiserClientWrapper::doRaise(
    apache::thrift::RpcOptions& rpcOptions) {
  folly::Promise<folly::Unit> _promise;
  auto _future = _promise.getFuture();
  auto callback = std::make_unique<::thrift::py3::FutureCallback<folly::Unit>>(
    std::move(_promise), rpcOptions, async_client->recv_wrapped_doRaise, channel_);
  async_client->doRaise(
    rpcOptions,
    std::move(callback)
  );
  return _future;
}

folly::Future<std::string>
RaiserClientWrapper::get200(
    apache::thrift::RpcOptions& rpcOptions) {
  folly::Promise<std::string> _promise;
  auto _future = _promise.getFuture();
  auto callback = std::make_unique<::thrift::py3::FutureCallback<std::string>>(
    std::move(_promise), rpcOptions, async_client->recv_wrapped_get200, channel_);
  async_client->get200(
    rpcOptions,
    std::move(callback)
  );
  return _future;
}

folly::Future<std::string>
RaiserClientWrapper::get500(
    apache::thrift::RpcOptions& rpcOptions) {
  folly::Promise<std::string> _promise;
  auto _future = _promise.getFuture();
  auto callback = std::make_unique<::thrift::py3::FutureCallback<std::string>>(
    std::move(_promise), rpcOptions, async_client->recv_wrapped_get500, channel_);
  async_client->get500(
    rpcOptions,
    std::move(callback)
  );
  return _future;
}


} // namespace cpp2
