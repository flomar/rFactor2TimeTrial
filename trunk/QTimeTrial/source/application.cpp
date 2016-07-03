// application.cpp

#include <application.h>

Application::Application(int &_argc, char **_argv) :
    QApplication(_argc, _argv),
    qmlApplicationEngine(0),
    applicationDatabase(0),
    applicationServer(0),
    applicationGui(0),
    configurationFileName(_argc == 2 ? QString(_argv[1]) : QString::null),
    applicationRoot(QString::null),
    applicationName(QString::null),
    applicationVersion(QString::null),
    applicationCopyright(QString::null),
    applicationDatabaseFileName(QString::null),
    applicationServerAddress(QString::null),
    applicationServerPort(QString::null) {

}

Application::~Application() {

}

bool Application::initialize() {
    // try to parse the configuration file
    if(!parseConfigurationFile(configurationFileName)) {
        qCritical() << QString("[CRITICAL] could not parse configuration file, please make sure to supply the absolute path to the configuration file as argument to the executable");
        return false;
    }
    // create application components
    applicationDatabase = new ApplicationDatabase(this);
    applicationServer = new ApplicationServer(this);
    applicationGui = new ApplicationGui(this);
    // create application QML engine
    qmlApplicationEngine = new QQmlApplicationEngine(this);
    // register individual components with application QML engine
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplication", this);
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationDatabase", applicationDatabase);
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationServer", applicationServer);
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationGui", applicationGui);
    // initialize application QML engine
    qmlApplicationEngine->load(getAbsoluteFilePath("resources/qml/application.qml"));
    // connect signals and slots between server and database: due to the design of this
    // application it is VERY IMPORTANT that messages from the server are first processed
    // by the database; after the database is finished processing the messages, it forwards
    // them to other internal components (see other signal/slot connections below)
    connect(applicationServer, SIGNAL(signalReceivedClientServerMessage(ClientServerMessage)), applicationDatabase, SLOT(slotReceivedClientServerMessage(ClientServerMessage)));
    // connect signals and slots between database and other internal components
    connect(applicationDatabase, SIGNAL(signalReceivedClientServerMessage(ClientServerMessage)), applicationGui, SLOT(slotReceivedClientServerMessage(ClientServerMessage)));
    // open the database
    if(!applicationDatabase->open(applicationDatabaseFileName)) {
        qCritical() << QString("[CRITICAL] could not open database file \"%1\"").arg(applicationDatabaseFileName);
        return false;
    }
    // start the server
    if(!applicationServer->start(applicationServerAddress, applicationServerPort)) {
        qCritical() << QString("[CRITICAL] could not listen to \"%1:%2\"").arg(applicationServerAddress).arg(applicationServerPort);
        return false;
    }
    // update the GUI
    applicationGui->update();
    return true;
}

bool Application::deinitialize() {
    // explicitly delete QML application angine
    delete qmlApplicationEngine;
    // stop the server
    if(!applicationServer->stop()) {
        return false;
    }
    // close the database
    if(!applicationDatabase->close()) {
        return false;
    }
    return true;
}

bool Application::parseConfigurationFile(const QString &_configurationFileName) {
    // the first thing we need to do is extract the application root
    QFileInfo configurationFileInfo(_configurationFileName);
    if(!configurationFileInfo.exists()) return false;
    applicationRoot = configurationFileInfo.absoluteDir().absolutePath();
    // read the configuration file and initialize the relevant variables
    ConfigurationFile configurationFile;
    if(!configurationFile.read(_configurationFileName.toStdString())) return false;
    // then we extract the remaining variables
    applicationName = configurationFile.getVariable("QTIMETRIAL_APPLICATION_NAME").c_str();
    applicationVersion = configurationFile.getVariable("QTIMETRIAL_APPLICATION_VERSION").c_str();
    applicationCopyright = configurationFile.getVariable("QTIMETRIAL_APPLICATION_COPYRIGHT").c_str();
    applicationDatabaseFileName = getAbsoluteFilePath("resources/sqlite/QTimeTrialDatabase.sqlite");
    applicationServerAddress = configurationFile.getVariable("QTIMETRIAL_APPLICATION_SERVER_ADDRESS").c_str();
    applicationServerPort = configurationFile.getVariable("QTIMETRIAL_APPLICATION_SERVER_PORT").c_str();
    // make sure all required variables are non-empty
    if(applicationRoot.isEmpty()) return false;
    if(applicationName.isEmpty()) return false;
    if(applicationVersion.isEmpty()) return false;
    if(applicationCopyright.isEmpty()) return false;
    if(applicationServerAddress.isEmpty()) return false;
    if(applicationServerPort.isEmpty()) return false;
    return true;
}

QString Application::getAbsoluteFilePath(const QString &_relativeFilePath) const {
    return QString("%1/%2").arg(applicationRoot).arg(_relativeFilePath);
}
