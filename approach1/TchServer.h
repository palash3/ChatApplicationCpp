/*
*   Class   : TcpServer
*   Purpose : This class enables user to create a tcp server and maintain the connection of incoming clients.
*   Author  : Palash Jain
*/

struct client_feilds{
    int fd;
    struct client_operation *cops;
};
struct client_operation{
    void (*onConnection)(struct client_feilds *);
    void (*data)(struct client_feilds * , char * );
    void (*close)(struct client_feilds *);
};

class TcpServer{
    private:
        int server_fd;
        int port_num;
    public:
        TcpServer(int port_num);
        int start();
        void acceptClients();
};