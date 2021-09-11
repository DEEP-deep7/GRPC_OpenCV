#include <ImageStream.grpc.pb.h>
#include <ImageStream.pb.h>
#include <opencv2/core/core.hpp>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/grpcpp.h>
#include <shared_mutex>
#include <memory>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using namespace cv;

class CVClient
{
public:
	CVClient(std::shared_ptr<Channel> channel);
	~CVClient();

	void HandleImageStream();

	void GetImgageStream();

	void CVHandle(std::string data , int row ,int clos);

	void CVHandle(cv::Mat image);

private:
	std::unique_ptr<CVServer::CVServer::Stub> m_stub;

};