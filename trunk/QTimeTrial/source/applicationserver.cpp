// applicationserver.cpp

#include <applicationserver.h>

#include <utilities.h>

ApplicationServer::ApplicationServer() {

}

ApplicationServer::~ApplicationServer() {

}

ApplicationServer &ApplicationServer::instance() {
    static ApplicationServer applicationServer;
    return applicationServer;
}

bool ApplicationServer::start(const quint16 _port) {
    if(!QTcpServer::listen(QHostAddress::LocalHost, _port)) {
        qCritical() << QString("[CRITICAL] could not listen to port %1").arg(_port);
        return false;
    }
    return true;
}

bool ApplicationServer::stop() {
    close();
    return true;
}

void ApplicationServer::incomingConnection(qintptr _socketDescriptor) {
    if(socket.setSocketDescriptor(_socketDescriptor)) {
        connect(&socket, SIGNAL(readyRead()), this, SLOT(slotSocketReadyRead()));
        connect(&socket, SIGNAL(disconnected()), qApp, SLOT(quit()));
    }
}

void ApplicationServer::slotSocketReadyRead() {
    const QByteArray byteArray = socket.readAll();
    ClientServerMessage message;
    memset(&message, 0, sizeof(message));
    memcpy(&message, byteArray, sizeof(message));
    emit signalReceivedClientServerMessage(message);
}
