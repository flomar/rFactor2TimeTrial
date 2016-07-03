// client.h

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "clientserverprotocol.h"

#include <winsock.h>

#include <string>

class Client {
public:
    Client();
    virtual ~Client();
public:
    bool connectToServer(const std::string &_serverAddress, const std::string &_serverPort);
    bool disconnectFromServer();
public:
    bool sendMessage(const ClientServerMessage &_message);
private:
    bool connected;
    SOCKET socketDescriptor;
};

#endif
