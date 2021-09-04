protoc -I. --grpc_out=. --plugin=protoc-gen-grpc="D:\\GRPC\\grpcBuild\\Release\\grpc_cpp_plugin.exe" ImageStream.proto
protoc --cpp_out=./ ImageStream.proto
pause
