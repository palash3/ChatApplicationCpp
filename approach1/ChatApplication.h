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
public:
    map <int , string> clientIdToName;
    map <string , int> nameToClientId;

    // will ask username to the client;
    // client must implement it
    int askUserName();
    int storeInMap(int clientId , string username);
    int getClientId(string);
    int removeFromMap(int );

    string getUsername(int);
    int interpretMessage(string message);
    int sendToRecipient(string  username);    
    ChatApplication();
};