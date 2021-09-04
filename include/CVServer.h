#include <grpcpp/grpcpp.h>
#include <ImageStream.grpc.pb.h>
#include <ImageStream.pb.h>
#include <opencv2/core/core.hpp>
#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace cv;


class CVImageServer final : public CVServer::CVServer::Service
{
public:
	CVImageServer();
	~CVImageServer();

	cv::Mat CVImageProcess();

	grpc::Status CVImageStream(::grpc::ServerContext* context,
		::grpc::ServerReaderWriter< ::CVServer::ImageMessage, ::CVServer::ImageMessage>* stream)  override;

	//注意参数与客户端的区别
	grpc::Status CVMatImageStream(::grpc::ServerContext* context, 
		::grpc::ServerReaderWriter< ::CVServer::ImageStream, ::CVServer::ImageStream>* stream)  override;

private:

};

