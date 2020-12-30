#include "TcpServer.h"
TcpServer::TcpServer(int port_num){
    // cout<<"in tcp server\n";
    this->port_num = port_num;
    max_fd=0;
    FD_ZERO(&read_fds);
    bzero(buf,1024);
}

int TcpServer::start(){
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd < 0){
        perror("Not able to make socket");
        return -1;
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family= AF_INET;
    server_addr.sin_addr.s_addr= INADDR_ANY;
    server_addr.sin_port = htons(port_num);
    int ret = bind(server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));    
    if(ret <0){
        perror("Not able to bind");
        return -1;
    }
    ret =listen(server_fd,10);
    if(ret <0){
        perror("Not able to listen");
        return -1;
    }
    max_fd=server_fd;
}

int TcpServer::acceptClients(){
    int ret =0;
    FD_SET(server_fd,&read_fds);
    fd_vec.push_back(server_fd);    
    while(1){
        fd_set tmp_set = read_fds;
        ret = select(max_fd+1,&tmp_set,NULL,NULL,NULL);
        if(ret<0){
            //select failed
        }
        int fd=0;
        for(fd=0;fd<=max_fd;fd++){
            if(FD_ISSET(fd,&tmp_set)){
                //checking for server connection
                if(fd == server_fd){
                    //if this should give me new connection
                    struct sockaddr client_info;
                    socklen_t client_info_len=0;
                    bzero(&client_info,sizeof(struct sockaddr));
                    ret =accept4(server_fd,&client_info,&client_info_len,SOCK_NONBLOCK);
                    if(ret<0){
                        perror("Accept failed");
                    }else{
                        //Here we have a new client
                        int client_fd = ret;
                        onConnection(client_fd);
                        FD_SET(client_fd,&read_fds);
                        fd_vec.push_back(client_fd);
                        //this logic should be improved
                        if(client_fd > max_fd){
                            max_fd = client_fd;
                        }
                        //-----------
                    }
                }else{
                    ret = recv(fd,buf,1024,MSG_DONTWAIT);
                    if(ret == 0){ // socket is closed
                        FD_CLR(fd,&read_fds);
                        onClose(fd);
                        fd_vec.erase(remove(fd_vec.begin(), fd_vec.end(),fd), fd_vec.end());
                        close(fd);
                    }
                    //should I allocate memory every time I send data , since multiple instances might hurt this implementation
                    if(ret >0){
                        onData(fd,buf,ret);
                        bzero(buf,ret+1);   
                    }
                }
            }
        }
    }
}


//we can make send non blocking and then return the status respectively
int TcpServer::sendToClient(int clientId , char* msg , int len){
    int sent_bytes=0;
    if(std::find(fd_vec.begin(),fd_vec.end(),clientId) != fd_vec.end()){
        sent_bytes = send(clientId,msg,len,0);
    }else{
        sent_bytes =-1;
    }
    return sent_bytes;
}