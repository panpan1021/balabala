#include"EchoServer.hpp"
#include<memory>
int main(){
    std::unique_ptr<udp_server> ptr=make_unique<udp_server>();
    ptr->init();
    ptr->start();
    return 0;
}