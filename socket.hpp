#pragma once

#include<iostream>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include"InetAddr.hpp"
#include<memory>
#include <cstdint>
#include <unistd.h>
namespace socket_name{
    static const int backlog=70;
    enum{
        SUCCESS=0,
        CREATE,
        BIND,
        RECV,
        SEND,
        ACCEPT,
        LISTEN,
    };
    class Socket{
        public:
        virtual void CreateOrDie()=0;
        virtual void Bind(uint16_t port)=0;
        virtual void Listen()=0; 
        virtual int socketfd()=0;
        virtual int Recv(std::string *)=0;
        virtual int Send(std::string &)=0;
        virtual void Close()=0;
        virtual std::shared_ptr<Socket> Accepter(InetAddr &addr) = 0;
        virtual bool Connect(InetAddr& addr)=0;
        virtual ~Socket()=default;
        void BuildServerTcpSocket(uint16_t port){
        CreateOrDie();
        Bind(port);
        Listen();
       }
       void BuildClientTcpSocket(){
        CreateOrDie();
       }
    };
    class TcpSocket:public Socket
    {
        public:
        TcpSocket():_sock(0){}
        TcpSocket(int sock){_sock=sock;}
        void CreateOrDie() override
        {
            _sock=socket(AF_INET,SOCK_STREAM,0);
            if(_sock<0)exit(CREATE);

        }
        void Bind(uint16_t port) override
        {   
            InetAddr addr(port);
            int n=bind(_sock,addr.NetAddress(),addr.Len());
            if(n!=0)exit(BIND);

        }
        void Listen()override{
            if(listen(_sock,backlog)!=0)exit(LISTEN);
        }
        std::shared_ptr<Socket> Accepter(InetAddr& clientaddr)override
        {
            struct sockaddr_in addr;
            socklen_t len=sizeof(addr);
            int sockfd=accept(_sock,CONV(&addr),&len);
            if(sockfd<0)
            {
                exit(ACCEPT);
            }
            clientaddr=addr;
            return std::make_shared<TcpSocket>(sockfd);
        }
       int socketfd() override
       {
        return _sock;
       }
      int Recv(std::string *out)override{
        char inbuffer[1024];
        ssize_t n=recv(_sock,inbuffer,sizeof(inbuffer)-1,0);
        if(n>0){
            inbuffer[n]=0;
            *out+=inbuffer;
        }
        return n;
       }
       int Send(std::string& in)override{
        return send(_sock,in.c_str(),in.size(),0);
      
    }
       void Close() override{
        if(_sock>=0)close(_sock);
        _sock=-1;
       }
       bool Connect(InetAddr& addr)override{
        int n=connect(_sock,addr.NetAddress(),addr.Len());
        if(n<0)return false;
        return true;
       }
        ~TcpSocket(){}
        private:
        int _sock;
    };
    
};