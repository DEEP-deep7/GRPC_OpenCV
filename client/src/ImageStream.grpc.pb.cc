// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: ImageStream.proto

#include "ImageStream.pb.h"
#include "ImageStream.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace CVServer {

static const char* CVServer_method_names[] = {
  "/CVServer.CVServer/CVImageStream",
  "/CVServer.CVServer/CVMatImageStream",
};

std::unique_ptr< CVServer::Stub> CVServer::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< CVServer::Stub> stub(new CVServer::Stub(channel, options));
  return stub;
}

CVServer::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_CVImageStream_(CVServer_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  , rpcmethod_CVMatImageStream_(CVServer_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::CVServer::ImageMessage, ::CVServer::ImageMessage>* CVServer::Stub::CVImageStreamRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::CVServer::ImageMessage, ::CVServer::ImageMessage>::Create(channel_.get(), rpcmethod_CVImageStream_, context);
}

void CVServer::Stub::async::CVImageStream(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::CVServer::ImageMessage,::CVServer::ImageMessage>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::CVServer::ImageMessage,::CVServer::ImageMessage>::Create(stub_->channel_.get(), stub_->rpcmethod_CVImageStream_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::CVServer::ImageMessage, ::CVServer::ImageMessage>* CVServer::Stub::AsyncCVImageStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::CVServer::ImageMessage, ::CVServer::ImageMessage>::Create(channel_.get(), cq, rpcmethod_CVImageStream_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::CVServer::ImageMessage, ::CVServer::ImageMessage>* CVServer::Stub::PrepareAsyncCVImageStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::CVServer::ImageMessage, ::CVServer::ImageMessage>::Create(channel_.get(), cq, rpcmethod_CVImageStream_, context, false, nullptr);
}

::grpc::ClientReaderWriter< ::CVServer::ImageStream, ::CVServer::ImageStream>* CVServer::Stub::CVMatImageStreamRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::CVServer::ImageStream, ::CVServer::ImageStream>::Create(channel_.get(), rpcmethod_CVMatImageStream_, context);
}

void CVServer::Stub::async::CVMatImageStream(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::CVServer::ImageStream,::CVServer::ImageStream>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::CVServer::ImageStream,::CVServer::ImageStream>::Create(stub_->channel_.get(), stub_->rpcmethod_CVMatImageStream_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::CVServer::ImageStream, ::CVServer::ImageStream>* CVServer::Stub::AsyncCVMatImageStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::CVServer::ImageStream, ::CVServer::ImageStream>::Create(channel_.get(), cq, rpcmethod_CVMatImageStream_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::CVServer::ImageStream, ::CVServer::ImageStream>* CVServer::Stub::PrepareAsyncCVMatImageStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::CVServer::ImageStream, ::CVServer::ImageStream>::Create(channel_.get(), cq, rpcmethod_CVMatImageStream_, context, false, nullptr);
}

CVServer::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CVServer_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< CVServer::Service, ::CVServer::ImageMessage, ::CVServer::ImageMessage>(
          [](CVServer::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::CVServer::ImageMessage,
             ::CVServer::ImageMessage>* stream) {
               return service->CVImageStream(ctx, stream);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CVServer_method_names[1],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< CVServer::Service, ::CVServer::ImageStream, ::CVServer::ImageStream>(
          [](CVServer::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::CVServer::ImageStream,
             ::CVServer::ImageStream>* stream) {
               return service->CVMatImageStream(ctx, stream);
             }, this)));
}

CVServer::Service::~Service() {
}

::grpc::Status CVServer::Service::CVImageStream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::CVServer::ImageMessage, ::CVServer::ImageMessage>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CVServer::Service::CVMatImageStream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::CVServer::ImageStream, ::CVServer::ImageStream>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace CVServer

