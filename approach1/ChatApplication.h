/*
*   Class   : ChatApplication
*   Purpose : This class enables user to create a tcp server and provide callback structure to maintain them.
*   Author  : Palash Jain
*/

#include "TcpServer.h"
#include <map>
#include <iterator>
#include <string>

using std::string;
using std::map;

class ChatApplication{
private:
    TcpServer server_obj;
    map <int , string> clientIdToName;
    // will ask username to the client;
    // client must implement it
    int askUserName();
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
    int storeInMap(int clientId , string username);
    int getClientId(string username);
    int interpretMessage(string message);
    int sendToRecipient(string  username);    
public:
    ChatApplication(int portNumber);
    int start();
};