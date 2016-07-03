// client.cpp

#include "client.h"

Client::Client() :
    connected(false),
    socketDescriptor(0) {

}

Client::~Client() {
    WSACleanup();
}

bool Client::connectToServer(const std::string &_serverAddress, const std::string &_serverPort) {

    //
    // TODO/FIXME: for now, client is always connecting to 127.0.0.1:9999
    //

    WSAData wsaData;
    if(WSAStartup(0x0202, &wsaData) != 0) return false;
    if(wsaData.wVersion != 0x0202) return false;
    SOCKADDR_IN server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_port = htons(9999);
    socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketDescriptor == INVALID_SOCKET) return false;
    if(connect(socketDescriptor, (struct sockaddr*)(&server), sizeof(server)) == SOCKET_ERROR) return false;
    connected = true;
    return true;
}

bool Client::disconnectFromServer() {
    if(socketDescriptor == INVALID_SOCKET) return false;
    closesocket(socketDescriptor);
    connected = false;
    return true;
}

bool Client::sendMessage(const ClientServerMessage &_message) {
    if(!connected) return false;
    return send(socketDescriptor, (const char*)(&_message), sizeof(_message), 0) != SOCKET_ERROR;
}
