#include "./TcpServer.h"

#include <sys/types.h>
#include <sys/socket.h>

TcpServer::TcpServer(int port_num){
    this.port_num = port_num;
}

int TcpServer::start(){
    this.server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(this.server_fd < 0){
        return -1;
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family= AF_INET;
    server_addr.sin_addr.s_addr= IADDR_ANY;
    server_addr.sin_port = htons(port_num);
    int ret = bind(this.server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));    
    if(ret <0){
        return -1;
    }
    ret =listen(server_fd,10);
    if(ret <0){
        return -1;
    }
}

void TcpServer::acceptClients(){
        
}