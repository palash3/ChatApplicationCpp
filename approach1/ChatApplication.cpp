#include "ChatApplication.h"
using namespace std;
ChatApplication::ChatApplication(){
    //may be backup old usernames
}

int ChatApplication::storeInMap(int clientId ,string name){
    //check for duplicacy then return false;
    clientIdToName.insert(pair < int , string > (clientId,name));
    nameToClientId.insert(pair < string , int > (name,clientId));
    return 1;
}

int ChatApplication::getClientId(string username){
    int occurences =nameToClientId.count(username);
    int clientId =-1;
    if(occurences >0){
        clientId = nameToClientId[username];
    }
    return clientId;
}

string ChatApplication::getUsername(int clientId){
    int occurences =clientIdToName.count(clientId);
    string username=NULL;
    if(occurences >0){
        username = clientIdToName[clientId];
    }
    return username;
}

int ChatApplication::removeFromMap(int clientId){
    int occurences =clientIdToName.count(clientId);
    if(occurences > 0){
        string name_to_be_deleted = clientIdToName[clientId];
        clientIdToName.erase(clientIdToName.find(clientId));
        nameToClientId.erase(nameToClientId.find(name_to_be_deleted));
    }
    return occurences;
}

