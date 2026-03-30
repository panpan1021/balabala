#pragma once
#include<iostream>
#include<string>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <string.h>
using namespace std;
enum{
    SUCCESS=0,
    SOCKET,
    BIND,
    RECV,
};
class udp_server{
public:
    udp_server(int port=8888)
    :_port(port)
    {}
    void init(){
        _socket=socket(AF_INET,SOCK_DGRAM,0);
        if(_socket<0){exit(SOCKET);}
        cout<<"socket right"<<endl;
        struct sockaddr_in local;
        bzero(&local,sizeof(local));
        local.sin_family=AF_INET;
        local.sin_port=htons(_port);
        local.sin_addr.s_addr=INADDR_ANY;
        int n=bind(_socket,(struct sockaddr*)&local,sizeof(local));
        if(n<0)exit(BIND);
    }
    void start(){
        char buffer[1024];
        for(;;){
            struct sockaddr_in peer;
            socklen_t len=sizeof(peer);
            int n=recvfrom(_socket,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&peer,&len);
            if(n==-1)exit(RECV);
            else{
                
                printf("%s\n",buffer);
                sendto(_socket,buffer,n,0,(const struct sockaddr*)&peer,len);
            }
        }
    }
private:
    int _socket;
    int _port;
};