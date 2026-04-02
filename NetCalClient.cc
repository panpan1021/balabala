#include<iostream>
#include"socket.hpp"
#include"Calculator.hpp"
#include<string>
using namespace socket_name;
static void Usage(const std::string &proc){
    std::cout<<"Usage:\n\t"<<proc<<"server_ip server_port"<<std::endl;
}
int main(int argc,char* argv[]){
    if(argc!=3){
        Usage(argv[0]);
        exit(1);
    }
    std::string ip=argv[1];
    uint16_t port=std::stoi(argv[2]);
    std::unique_ptr<Socket> socket=std::make_unique<TcpSocket>();
    socket->BuildClientTcpSocket();
    InetAddr serveraddress(port,ip);
    bool n=socket->Connect(serveraddress);
    if(!n)exit(2);
    Protocol protocol;
    std::string inbuffer;
    while(true){
        int x,y;
        char oper;
        std::cout<<"Enter your x"<<std::endl;
        std::cin>>x;
        std::cout<<"Enter your y"<<std::endl;
        std::cin>>y;
        std::cout<<"Enter your oper"<<std::endl;
        std::cin>>oper;
        Request req(x,y,oper);
        std::string req_json;
        req.Serialize(&req_json);
        std::string send_req_string=protocol.Packet(req_json);
        socket->Send(send_req_string);
        socket->Recv(&inbuffer);
        protocol.ParseResponse(inbuffer);
    }
    socket->Close();
    return 0;
}