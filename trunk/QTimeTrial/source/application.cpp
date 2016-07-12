// application.cpp

#include <application.h>

Application::Application(int &_argc, char **_argv) :
    QApplication(_argc, _argv),
    qmlApplicationEngine(0),
    applicationDatabase(0),
    applicationServer(0),
    applicationGui(0),
    applicationDatabaseFileName(_argc == 4 ? QString(_argv[1]) : QString::null),
    applicationServerAddress(_argc == 4 ? QString(_argv[2]) : QString::null),
    applicationServerPort(_argc == 4 ? QString(_argv[3]) : QString::null) {

}

Application::~Application() {

}

bool Application::initialize() {
    // for this application to work properly, three arguments must be
    // supplied to the executable: the path to the database file, the
    // server address, and the server port; if any of the corresponding
    // variables is empty at this point (they should have been set at
    // construction, see above), something is wrong
    if(applicationDatabaseFileName.isEmpty() || applicationServerAddress.isEmpty() || applicationServerPort.isEmpty()) {
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("Ooops... something went wrong!\n\nPlease make sure all the required arguments have been supplied to the executable: the path to the database file, the server address, and the server port.");
        messageBox.exec();
        return false;
    }
    // create application components
    applicationDatabase = new ApplicationDatabase(this);
    applicationServer = new ApplicationServer(this);
    applicationGui = new ApplicationGui(this);
    // connect signals and slots between server and database: due to the design of this
    // application it is VERY IMPORTANT that messages from the server are first processed
    // by the database; after the database is finished processing the messages, it forwards
    // them to other internal components (see other signal/slot connections below)
    connect(applicationServer, SIGNAL(signalReceivedClientServerMessage(ClientServerMessage)), applicationDatabase, SLOT(slotReceivedClientServerMessage(ClientServerMessage)));
    // connect signals and slots between database and other internal components
    connect(applicationDatabase, SIGNAL(signalReceivedClientServerMessage(ClientServerMessage)), applicationGui, SLOT(slotReceivedClientServerMessage(ClientServerMessage)));
    // open the database
    if(!applicationDatabase->open(applicationDatabaseFileName)) {
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText(QString("The database file \"%1\" could not be opened.").arg(applicationDatabaseFileName));
        messageBox.exec();
        return false;
    }
    // start the server
    if(!applicationServer->start(applicationServerAddress, applicationServerPort)) {
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText(QString("The server could not listen to \"%1:%2\".").arg(applicationServerAddress).arg(applicationServerPort));
        messageBox.exec();
        return false;
    }
    // create application QML engine
    qmlApplicationEngine = new QQmlApplicationEngine(this);
    // register individual components with application QML engine
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplication", this);
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationDatabase", applicationDatabase);
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationServer", applicationServer);
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationGui", applicationGui);
    // register database models with application QML engine
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationDatabaseModelOptions", applicationDatabase->getModelOptions());
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationDatabaseModelDrivers", applicationDatabase->getModelDrivers());
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationDatabaseModelSessions", applicationDatabase->getModelSessions());
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationDatabaseModelRuns", applicationDatabase->getModelRuns());
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationDatabaseModelLaps", applicationDatabase->getModelLaps());
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationDatabaseModelRecords", applicationDatabase->getModelRecords());
    // initialize application QML engine
    qmlApplicationEngine->load(QUrl("qrc:/qml/application.qml"));
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
