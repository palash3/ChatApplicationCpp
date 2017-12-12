#include "TcpServer.h"

#include <iostream>
#include <algorithm>
using namespace std;


TcpServer::TcpServer(int port_num){
    this->port_num = port_num;
    max_fd=0;
    FD_ZERO(&read_fds);
    bzero(buf,1024);
}

int TcpServer::start(){
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd < 0){
        cout<<"Not able to make socket"<<server_fd;
        return -1;
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family= AF_INET;
    server_addr.sin_addr.s_addr= INADDR_ANY;
    server_addr.sin_port = htons(port_num);
    int ret = bind(server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));    
    if(ret <0){
        cout<<"Not able to bind"<<ret;
        return -1;
    }
    ret =listen(server_fd,10);
    if(ret <0){
        cout<<"Not able to listen"<<ret;
        return -1;
    }
    max_fd=server_fd;
    
    read_fd_vec.push_back(server_fd);
}
void TcpServer::registerClientCallbacks(struct client_operation * ctr ){
    if(ctr->onConnection){
        client_callbacks.onConnection = ctr->onConnection;
    }
    if(ctr->data){
        client_callbacks.data = ctr->data;
    }
    if(ctr->close){
        client_callbacks.close = ctr->close;
    }
}
int TcpServer::acceptClients(){
    if(max_fd == 0){
        //call start first
        return -1;
    }
    int ret =0;
    while(1){
        
        FD_SET(server_fd,&read_fds);
        cout<<"Over select ---------"<<max_fd<<endl;
        int i=0;
        ret = select(max_fd+1,&read_fds,NULL,NULL,NULL);
        cout <<"select call done "<<max_fd << ret<<endl;
        if(ret<0){
            //select failed
          //  return ret;
        }
        int fd=0;
        for(fd=0;fd<=max_fd+1;fd++){
            if(FD_ISSET(fd,&read_fds)){
                //checking for server connection
                if(fd == server_fd){
                    //if tris should give me new connection
                    cout<<"Got a client"<<endl;
                    struct sockaddr client_info;
                    socklen_t client_info_len;
                    cout<<"Over accept---";
                    ret =accept4(server_fd,&client_info,&client_info_len,SOCK_NONBLOCK);
                    cout<<"out of accept"<<endl;
                    if(ret<0){
                        cout<<"Accept failed "<<ret<<endl;
                        //  return ret;
                    }else{
                        //Here we have a new client
                        int client_fd = ret;
                        client_callbacks.onConnection(client_fd);
                        FD_SET(client_fd,&read_fds);
                        read_fd_vec.push_back(client_fd);
                        //this logic should be improved
                        if(client_fd > max_fd){
                            max_fd = client_fd;
                        }
                        //-----------
                    }
                }else{
                    cout<<"Over Recv---";
                    ret = recv(fd,buf,1024,MSG_DONTWAIT);
                    cout<<"out of recv"<<endl;
                    if(ret == 0){ // socket is closed
                        cout <<"closing fd "<<fd<<endl;
                        FD_CLR(fd,&read_fds);
                        client_callbacks.close(fd);
                        ret = close(fd);
                        cout<<"ret of close"<<ret<<endl;
                    }
                    if(ret<0){
                        //error did not read properly
                        cout<<"ret of read"<<ret<<endl;
                    }
                    //should I allocate memory every time I send data , since multiple instances might hurt this implementation
                    if(ret >0){
                        client_callbacks.data(fd,buf,ret);
                        bzero(buf,ret+1);   
                    }
                }
            }
        }
    }
}