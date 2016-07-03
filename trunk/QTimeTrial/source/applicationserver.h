// applicationserver.h

#ifndef _APPLICATIONSERVER_H_
#define _APPLICATIONSERVER_H_

#include <main.h>

class Application;

class ApplicationServer : public QTcpServer {
    Q_OBJECT
public:
    ApplicationServer(Application *_application);
    virtual ~ApplicationServer();
private:
    Application *application;
public:
    bool start(const quint16 _port);
    bool stop();
protected:
    virtual void incomingConnection(qintptr _socketDescriptor);
private slots:
    void slotSocketReadyRead();
signals:
    void signalReceivedClientServerMessage(const ClientServerMessage &_message);
private:
    QTcpSocket socket;
};

#endif
