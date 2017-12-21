#include <iostream>
using namespace std;
#include "ChatApplication.h"
#include "TcpServer.h"
void onConnection (int client_id);
void data (int client_id, char * data ,int datalen);
void close_client (int client_id);
TcpServer server_obj(9096);
struct client_operation c_ops={
    //void (*onConnection)(int client_id);
    .onConnection=onConnection,
    //void (*data)(int client_id, char * data ,int datalen);
    .data=data,
    //void (*close)(int client_id);
    .close=close_client
};

class XYZ{
public:
    void onConnection (int client_id){
        cout<<"Client connected "<<client_id<<endl;
    }
    void data (int client_id, char * data ,int datalen){
        cout<<"Client "<<client_id << data<<datalen<< endl;
        server_obj.sendToClient(client_id,"OK!",3);
    }
    void close_client (int client_id){
        cout<<"Client CLosed "<<client_id<<endl;
     }
      
};

XYZ temp_obj;





ChatApplication chat(2020);

void onConnection(int client_id){
    cout<<"Client connected "<<client_id<<endl;
}

void data(int client_id,char *data, int len){
    cout<<"Client "<<client_id << data<<len<< endl;
    server_obj.sendToClient(client_id,"OK!",3);
}
void close_client(int client_id){
   cout<<"Client CLosed "<<client_id<<endl;
}

int main(){
    struct client_operation temp_c_ops={
        //void (*onConnection)(int client_id);
        .onConnection=(void (*)(int))&temp_obj.onConnection,
        //void (*data)(int client_id, char * data ,int datalen);
        .data=(void (*)(int, char*, int))&temp_obj.data,
        //void (*close)(int client_id);
        .close=(void (*)(int))&temp_obj.close_client
    };
    cout <<"Object created"<< endl;
    server_obj.registerClientCallbacks(&c_ops);
    cout <<"Registered Callbacks"<< endl;
    server_obj.start();
    cout <<"Started obj"<< endl;
    server_obj.acceptClients();
    cout <<"Accepting clients"<< endl;
    while(1);
    return 0;
}
