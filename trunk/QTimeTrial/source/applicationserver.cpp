// applicationserver.cpp

#include <applicationserver.h>
#include <application.h>

ApplicationServer::ApplicationServer(Application *_application) :
    QTcpServer(_application) {

}

ApplicationServer::~ApplicationServer() {

}

bool ApplicationServer::start(const QString &_serverAddress, const QString &_serverPort) {
    if(!QTcpServer::listen(QHostAddress(_serverAddress), _serverPort.toUInt())) {
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
