#pragma once
#include"socket.hpp"
#include"InetAddr.hpp"
#include<memory>
#include<functional>
using Handler_t=std::function<std::string(std::string&)>;
using namespace socket_name;
class TcpServer
{
    public:
    TcpServer(Handler_t handler,uint16_t port=8888):
    _port(port)
    ,_listensock(std::make_unique<TcpSocket>())
    ,_handler(handler){
        _listensock->BuildServerTcpSocket(_port);
    }
    void loop(){
        while(true){
             InetAddr clientaddr;
            auto sockfd=_listensock->Accepter(clientaddr);
            if(!sockfd)
            continue;
            if(fork()==0){
                //child
                service(sockfd,clientaddr);
                sockfd->Close();
                exit(0);
            }
        }
    }
    private:
    void service(std::shared_ptr<Socket> sockfd,InetAddr& clientaddr)
    {
        std::string inbuffer,outbuffer;
     while(true){
        outbuffer.clear();
        int n=sockfd->Recv(&inbuffer);
        if(n<=0)break;
        outbuffer+=_handler(inbuffer);
        int m=sockfd->Send(outbuffer);
        if(m<0)break;
    }
}
    private:
    uint16_t _port;
    std::unique_ptr<Socket>  _listensock;
    Handler_t _handler;
};