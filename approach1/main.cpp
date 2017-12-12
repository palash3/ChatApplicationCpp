#include <iostream>

using namespace std;


#include "TcpServer.h"
void onConnection (int client_id);
void data (int client_id, char * data ,int datalen);
void close_client (int client_id);

struct client_operation c_ops={
    //void (*onConnection)(int client_id);
    .onConnection=onConnection,
    //void (*data)(int client_id, char * data ,int datalen);
    .data=data,
    //void (*close)(int client_id);
    .close=close_client
};

void onConnection(int client_id){
    cout<<"Client connected "<<client_id<<endl;
}

void data(int client_id,char *data, int len){
    cout<<"Client "<<client_id << data<<len<< endl;
}
void close_client(int client_id){
   cout<<"Client CLosed "<<client_id<<endl;
}

int main(){
    TcpServer server_obj(9096);
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
