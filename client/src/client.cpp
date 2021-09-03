#include "../client/include/CVClient.h"

int main(int argc, char** argv)
{
	CVClient client(grpc::CreateChannel("localhost:50052", 
		grpc::InsecureChannelCredentials()));
	std::cout << "start handle image stream" << std::endl;
	client.HandleImageStream();
	return 0;
}