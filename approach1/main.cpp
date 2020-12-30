#include <iostream>
#include "TcpServer.h"
#include "ChatApplication.h"

using namespace std;


class XYZ : public TcpServer
{   
    
    ChatApplication ch;

    public :
    XYZ(int port_num):TcpServer(port_num){
        ch = ChatApplication();
    }
    int print(){
        cout<<"Print from XYZ";
    }
    void onConnection(int fd){
        cout<<"Connected "<<fd<<endl;
        char client_uuid[21];
        sprintf(client_uuid, "uuid%d", fd);
        ch.storeInMap(fd,client_uuid);
        char msg[50];
        sprintf(msg, "Your name is ->%s",client_uuid);
        int ret = sendToClient(fd,msg,strlen(msg));
        cout<<"Name assigned by server"<<client_uuid<<" Return is "<<ret<<endl;
    } 
    void onData(int fd, char * data ,int len ){
        if (len == 0){
            return;
        }
        char *token = strtok(data, ":");
        if (token == NULL){
            char msg[50] = "Correct format is username:message";
            sendToClient(fd,msg,strlen(msg));
            return;
        }
        int client_id = ch.getClientId(token);
        if (client_id == -1){
            char msg[50] = "User not found";
            sendToClient(fd,msg,strlen(msg));
            return;
        }
        char *sent_msg;
        sent_msg = strtok(data, ":");
        sendToClient(client_id,sent_msg,strlen(sent_msg));
    }
    void onClose(int fd ){

    }
    
};

int main (){
        cout<<"Hello there"<<endl;
        XYZ z(5001);
        z.print();
        z.start();
        z.acceptClients();
        return 0;
}
