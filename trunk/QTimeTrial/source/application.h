// application.h

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <main.h>

#include <applicationdatabase.h>
#include <applicationserver.h>
#include <applicationgui.h>

#include <utilities.h>

#define QTIMETRIAL_APPLICATION_NAME "QTimeTrial"
#define QTIMETRIAL_APPLICATION_COPYRIGHT "(C) 2016 flomar"

class Application : public QApplication {
    Q_OBJECT
public:
    Application(int &_argc, char **_argv);
    virtual ~Application();
public:
    bool initialize();
    bool deinitialize();
private:
    QQmlApplicationEngine *qmlApplicationEngine;
private:
    ApplicationDatabase *applicationDatabase;
    ApplicationServer *applicationServer;
    ApplicationGui *applicationGui;
public:
    ApplicationDatabase *getApplicationDatabase() { return applicationDatabase; }
    ApplicationServer *getApplicationServer() { return applicationServer; }
    ApplicationGui *getApplicationGui() { return applicationGui; }
public:
    const ApplicationDatabase *getApplicationDatabaseConst() const { return applicationDatabase; }
    const ApplicationServer *getApplicationServerConst() const { return applicationServer; }
    const ApplicationGui *getApplicationGuiConst() const { return applicationGui; }
private:
    const QString applicationDatabaseFileName;
    const QString applicationServerAddress;
    const QString applicationServerPort;
public:
    const QString &getApplicationDatabaseFileName() const { return applicationDatabaseFileName; }
    const QString &getApplicationServerAddress() const { return applicationServerAddress; }
    const QString &getApplicationServerPort() const { return applicationServerPort; }
};

#endif
