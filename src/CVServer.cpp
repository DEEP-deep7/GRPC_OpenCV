#include "CVServer.h"
#include <chrono>

using std::chrono::system_clock;

CVImageServer::CVImageServer()
{
}

CVImageServer::~CVImageServer()
{
}

cv::Mat CVImageServer::CVImageProcess()
{
	Mat src, dest;
	src = imread("C:/Users/gl/Desktop/Temp/photo.png");
	//namedWindow("测试opencv", WINDOW_AUTOSIZE);
	//imshow("测试opencv", src);

	dest.create(src.size(), src.type());
	//像素操作 滤波器
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (src.channels() == 3)  //通道值为3  可以对以下三个通道进行操作
			{
				int b = src.at<Vec3b>(i, j)[0];
				int g = src.at<Vec3b>(i, j)[1];
				int r = src.at<Vec3b>(i, j)[2];
				//dest.at<Vec3b>(i, j)[0] =  b; 
				//dest.at<Vec3b>(i, j)[1] =  g;
				//if (r < 204 && r > 202 && b < 38 && b > 36 && g < 35 && g > 33)
				if (r >= 200)
				{
					dest.at<Vec3b>(i, j)[2] = 255;
					dest.at<Vec3b>(i, j)[0] = 255;
					dest.at<Vec3b>(i, j)[1] = 255;
				}

			}
		}
	}
	std::cout << "colorb:" << int(dest.at<Vec3b>(5, 10)[0]) << std::endl;
	std::cout << "colorg:" << int(dest.at<Vec3b>(5, 10)[1]) << std::endl;
	std::cout << "colorr:" << int(dest.at<Vec3b>(5, 10)[2]) << std::endl;
	std::cout << "rows::" << int(dest.rows) << std::endl;
	std::cout << "size::" << dest.size()<< std::endl;
	std::cout << "value:" << int(src.at<Vec3b>(1, 0)[0])<<"," << int(src.at<Vec3b>(1, 0)[1]) << "," << int(src.at<Vec3b>(1, 0)[2]) << std::endl;
	//对应接口
	//bitwise_not(src, dest);

	//namedWindow("测试opencv2", WINDOW_AUTOSIZE);
	//imshow("测试opencv2", dest);

	//waitKey(0);
	return src;
}

grpc::Status CVImageServer::CVImageStream(::grpc::ServerContext* context,
	::grpc::ServerReaderWriter<::CVServer::ImageMessage, ::CVServer::ImageMessage>* stream)
{
	std::cout << "start server" <<std::endl;
	CVServer::ImageMessage tempMessage;
	Mat src = CVImageProcess();
	int tempsize = src.rows * src.cols;
	system_clock::time_point start_time = system_clock::now();
	while (stream->Read(&tempMessage))
	{
		std::cout << "Read:" << tempMessage.command() << std::endl;

	}
	CVServer::ImageMessage Package;
	Package.set_command("picture");

	//Package.set_state(tempsize);
	//char mat[] = { reinterpret_cast<char>(src.data) };
	Package.set_row(src.rows);
	Package.set_colum(src.cols);
	std::cout << "set Package over:"<< tempsize << std::endl;
	
	char* mmat = new char[tempsize*3];
	memset(mmat,0 ,sizeof(char)*tempsize);
	std::cout << "rows*cols:" << tempsize;
	//memcpy(mmat,src.ptr<uchar>(0),tempsize);
	size_t len = strlen((src.ptr<char>(1)));
	std::cout << "matlen:" << len <<std::endl;
	std::cout << "value:" << *(src.ptr<uchar>(1));
	for (int i = 0; i < src.rows; i++)
	{
		std::cout << "rows:" << i;
		for (int j = 0; j < src.cols; j+=3)
		{
			//std::cout << "cols:" << j <<std::endl;
			mmat[i * src.rows + j] = src.at<Vec3b>(i, j)[2];
			mmat[i * src.rows + j+1] = src.at<Vec3b>(i, j)[0];
			mmat[i * src.rows + j+2] = src.at<Vec3b>(i, j)[1];
		}
		
	}
	//memcpy(mmat, src.data, tempsize);
	std::cout << "set Package over" << std::endl;
	//Package.set_imagestream(0, mmat);
	stream->Write(Package);
	std::cout << "Write over" << std::endl;
	delete[] mmat;
	system_clock::time_point over_time = system_clock::now();
	if (!tempMessage.command().empty())
	{
		std::cout << "handle over" << std::endl;
	}
	else
	{
		std::cout << "error:empty command" << std::endl;
	}
	return grpc::Status::OK;
}

grpc::Status CVImageServer::CVMatImageStream(::grpc::ServerContext * context, 
	::grpc::ServerReaderWriter<::CVServer::ImageStream, ::CVServer::ImageStream>* stream)
{
	std::cout << "start server" << std::endl;
	//CVServer::ImageMessage tempMessage;
	CVServer::ImageStream tempStream;
	Mat src = CVImageProcess();
	CVServer::Chunk tempChunk;
	
	stream->Read(&tempStream);
	std::cout << "command:" << tempStream.imgdata().command();

	//将图像数据读出并存储
	
	std::vector<CVServer::ImageStream> ImageData;
	//首行数据
	CVServer::ImageStream* firstLine = new CVServer::ImageStream();
	CVServer::ImageMessage imgdata;
	imgdata.set_channel(src.channels());
	imgdata.set_row(src.rows);
	imgdata.set_colum(src.cols);
	imgdata.set_type(src.type());
	firstLine->set_allocated_imgdata(&imgdata);

	ImageData.push_back(*firstLine);
	delete firstLine;

	//所有图像数据
	 
	//CVServer::ImageStream LineData;//声明行像素
	for (int i = 0; i < src.rows; i++)
	{
		CVServer::ImageStream LineData;
		
		for (int j = 0; j < src.cols; j++)
		{
			CVServer::Chunk* mat = LineData.add_linedata(); //声明单个像素
			uchar *pb = src.ptr<uchar>(i, j);
			//单通道、三通道、四通道
			switch (src.channels())
			{
			case 1:
				mat->set_pic_data0(int(pb[0]));
				break;
			case 3:
				mat->set_pic_data0(int(pb[0]));
				mat->set_pic_data1(int(pb[1]));
				mat->set_pic_data2(int(pb[2]));
				break;
			case 4:
				mat->set_pic_data0(int(pb[0]));
				mat->set_pic_data1(int(pb[1]));
				mat->set_pic_data2(int(pb[2]));
				mat->set_pic_data3(int(pb[3]));
				break;
			default:
				std::cerr << "channel error:" << src.channels() << std::endl;
				break;
			}

		}
		ImageData.push_back(LineData);
	}

	//逐行发送图像
	system_clock::time_point start_time = system_clock::now();
	
	for (int i = 0; i < ImageData.size(); i++)
	{
		stream->Write(ImageData[i]);
	}
	system_clock::time_point over_time = system_clock::now();

	return grpc::Status::OK;
}