/*
*   Class   : TcpServer
*   Purpose : This class enables user to create a tcp server and provide callback structure to maintain them.
*   Author  : Palash Jain
*/

#ifndef _TCPSERVER_IDF
#define _TCPSERVER_IDF

#include <unistd.h>
#include <netinet/ip.h>

#include <sys/types.h>

#include <sys/select.h>
#include <strings.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
using namespace std;

struct client_feilds{
    int fd;
    struct client_operation *cops;
};
struct client_operation{
    void (*onConnection)(int );
    void (*data)(int , char * ,int );
    void (*close)(int );
};

class TcpServer{
    private:
        int server_fd;
        int port_num;
        struct client_operation client_callbacks;
        fd_set read_fds;
        vector <int> read_fd_vec;
        int max_fd;
        char buf[1024];
    public:
        TcpServer(int port_num);
        int start();
        void registerClientCallbacks(struct client_operation * ctr );
        int acceptClients();
};

#endif