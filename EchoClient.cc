#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string>
#include<string.h>
#include <unistd.h>
using namespace std;
enum{
    SUCCESS,
    SOCKET,
    RECV,
    SEND,
};
int main(int argc,char* argv[]){
    if(argc!=3){
        cout<<"参数错误";
        exit(1);
    }
    string ip=argv[1];
    int port=stoi(argv[2]);
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0)exit(SOCKET);
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    inet_pton(AF_INET, ip.c_str(), &server.sin_addr);
    for(;;){
        string buffer;
        getline(cin,buffer);
        int n=sendto(sock,buffer.c_str(),buffer.size(),0,(struct sockaddr*)&server,sizeof(server));
        if(n>0){
            char inbuffer[1024];
            struct sockaddr_in tmp;
            socklen_t len=sizeof(tmp);
            bzero(&tmp,sizeof(tmp));
            int m=recvfrom(sock,inbuffer,sizeof(inbuffer),0,(struct sockaddr*)&tmp,&len);
            if(m<0)exit(RECV);
            inbuffer[m]=0;
            printf("%s\n",inbuffer);
            
        }
        else exit(SEND);    
        
    
    }
    close(sock);
    return 0;
}