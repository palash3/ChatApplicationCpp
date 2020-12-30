/*
*   Class   : TcpServer
*   Purpose : This class enables user to create a tcp server and provide callback structure to maintain them.
*   Author  : Palash Jain
*/

#ifndef _TCPSERVER_IDF
#define _TCPSERVER_IDF

#include <unistd.h>
#include <netinet/ip.h>
#include <algorithm>
#include <vector>
#include <sys/types.h>
#include <sys/select.h>
#include <strings.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>


class TcpServer{
    private:
        int server_fd;
        int port_num;
        fd_set read_fds;
        std::vector <int> fd_vec;
        int max_fd;
        char buf[1024];
    public:
        TcpServer(){};
        TcpServer(int port_num);
        int start();
        virtual void onConnection(int) = 0; 
        virtual void onData(int , char * ,int )=0;
        virtual void onClose(int )=0;
        int acceptClients();
        int sendToClient(int clientId , char* msg , int length);
};

#endif