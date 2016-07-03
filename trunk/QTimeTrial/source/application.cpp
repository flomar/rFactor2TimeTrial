// application.cpp

#include <application.h>
#include <applicationdatabase.h>
#include <applicationgui.h>
#include <applicationserver.h>

#include <utilities.h>

Application::Application(int &_argc, char **_argv) :
    QApplication(_argc, _argv),
    configurationFileName(_argc == 2 ? QString(_argv[1]) : QString::null),
    applicationRoot(QString::null),
    applicationName(QString::null),
    applicationVersion(QString::null),
    applicationCopyright(QString::null),
    applicationServerAddress(QString::null),
    applicationServerPort(QString::null) {

}

Application::~Application() {

}

bool Application::initialize() {
    // try to open the configuration file
    if(!configurationFile.read(configurationFileName.toStdString())) {
        qCritical() << QString("[CRITICAL] could not read configuration file, please make sure to supply the absolute path to the configuration file as argument to the executable");
        return false;
    }
    // the next thing we need to do is extract the application root
    QFileInfo configurationFileInfo(configurationFileName);
    applicationRoot = configurationFileInfo.absoluteDir().absolutePath();
    // then we extract the remaining variables
    applicationName = configurationFile.getVariable("QTIMETRIAL_APPLICATION_NAME").c_str();
    applicationVersion = configurationFile.getVariable("QTIMETRIAL_APPLICATION_VERSION").c_str();
    applicationCopyright = configurationFile.getVariable("QTIMETRIAL_APPLICATION_COPYRIGHT").c_str();
    applicationServerAddress = configurationFile.getVariable("QTIMETRIAL_APPLICATION_SERVER_ADDRESS").c_str();
    applicationServerPort = configurationFile.getVariable("QTIMETRIAL_APPLICATION_SERVER_PORT").c_str();
    // make sure all required variables are non-empty
    if(applicationRoot.isEmpty()) return false;
    if(applicationName.isEmpty()) return false;
    if(applicationVersion.isEmpty()) return false;
    if(applicationCopyright.isEmpty()) return false;
    if(applicationServerAddress.isEmpty()) return false;
    if(applicationServerPort.isEmpty()) return false;

    // TODO/FIXME: honor application root when using relative resource paths (fonts, images, etc.),
    // not just in the Qt code here, but also in the QML code all over the place

    // add some fonts
    QFontDatabase::addApplicationFont("resources/fonts/Bitwise.ttf");
    // create application QML engine
    QQmlApplicationEngine *qmlApplicationEngine = new QQmlApplicationEngine(this);
    // register individual components with application QML engine
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplication", this);
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationDatabase", &ApplicationDatabase::instance());
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationGui", &ApplicationGui::instance());
    qmlApplicationEngine->rootContext()->setContextProperty("QTimeTrialApplicationServer", &ApplicationServer::instance());
    // initialize application QML engine
    qmlApplicationEngine->load(QUrl("resources/qml/application.qml"));
    // connect signals and slots between server and database: due to the design of this
    // application it is VERY IMPORTANT that messages from the server are first processed
    // by the database; after the database is finished processing the messages, it forwards
    // them to other internal components (see other signal/slot connections below)
    connect(&ApplicationServer::instance(), SIGNAL(signalReceivedClientServerMessage(ClientServerMessage)), &ApplicationDatabase::instance(), SLOT(slotReceivedClientServerMessage(ClientServerMessage)));
    // connect signals and slots between database and other internal components
    connect(&ApplicationDatabase::instance(), SIGNAL(signalReceivedClientServerMessage(ClientServerMessage)), &ApplicationGui::instance(), SLOT(slotReceivedClientServerMessage(ClientServerMessage)));
    // open the database
    if(!ApplicationDatabase::instance().open("QTimeTrialDatabase.sqlite")) {
        return false;
    }
    // update the GUI
    ApplicationGui::instance().update();
    // start the server on port 9999
    if(!ApplicationServer::instance().start(9999)) {
        return false;
    }
    return true;
}

bool Application::deinitialize() {
    // stop the server
    if(!ApplicationServer::instance().stop()) {
        return false;
    }
    // close the database
    if(!ApplicationDatabase::instance().close()) {
        return false;
    }
    return true;
}
