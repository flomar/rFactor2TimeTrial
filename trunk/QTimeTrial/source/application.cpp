// application.cpp

#include <application.h>
#include <applicationdatabase.h>
#include <applicationgui.h>
#include <applicationserver.h>

#include <utilities.h>

Application::Application(int &_argc, char **_argv) :
    QApplication(_argc, _argv) {

}

Application::~Application() {

}

bool Application::initialize() {
    // add some fonts
    QFontDatabase::addApplicationFont("resources/fonts/Bitwise.ttf");
    QFontDatabase::addApplicationFont("resources/fonts/Copperplate.ttf");
    QFontDatabase::addApplicationFont("resources/fonts/Impact.ttf");
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
