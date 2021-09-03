#include "..\include\CVClient.h"
#include <iostream>
#include <vector>

CVClient::CVClient(std::shared_ptr<Channel> channel) 
{
    m_stub = CVServer::CVServer::NewStub(channel);
}

CVClient::~CVClient()
{
}

void CVClient::HandleImageStream()
{
    std::string command;
    std::cout << "intput command" << std::endl;
    std::cin >> command;
    std::cout << "command is:" << command <<std::endl;
    ClientContext context;
    std::shared_ptr<ClientReaderWriter<CVServer::ImageMessage, CVServer::ImageMessage> > stream(
        m_stub->CVImageStream(&context));  //where is it different with server

    std::thread writer([stream,command]() {
        std::cout << "Client setPkg" << std::endl;
        CVServer::ImageMessage commandPkg;
        commandPkg.set_command(command);
        commandPkg.set_colum(0);
        commandPkg.set_row(0);
        commandPkg.set_state(0);
        //commandPkg.set_imagestream(1, "asdfasdf");//为什么这么写会导致客户端崩溃
        std::cout << "Client Write" << std::endl;
        stream->Write(commandPkg);
        stream->WritesDone();
        std::cout << "write over" << std::endl;
        stream->WritesDone();
        });
    
    CVServer::ImageMessage ImagePackage;
    
    int size = 0;
    int rows = 0;
    int clos = 0;
    while (stream->Read(&ImagePackage))
    {
        //stream data 
        std::cout << "client read data" << std::endl;
        size = ImagePackage.state();
        rows = ImagePackage.row();
        clos = ImagePackage.colum();
        //ImagePackage.imagestream().data();
    }
    std::string strbuf = ImagePackage.imagestream().Get(0);
    std::cout << "strbuff size:" << strbuf.size() << std::endl;
    std::cout << "net work stream size:" << size << std::endl;
    CVHandle(strbuf,rows,clos);

    Status stuts = stream->Finish();
    if (!stuts.ok())
    {
        std::cout << "error : ImageStream is failed" << std::endl;
    }
}

void CVClient::CVHandle(std::string data, int row, int clos)
{
    std::cout << "CVHandle" << std::endl;
    Mat src(row,clos, CV_8UC1);
    const char* matdata = data.data();
    namedWindow("测试opencv", WINDOW_AUTOSIZE);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < clos; j++)
        {
            src.at<uchar>(i,j) = matdata[i * row + j];
        }
    }

    imshow("测试opencv", src);
}
