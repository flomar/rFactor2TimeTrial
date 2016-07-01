// applicationgui.cpp

#include <applicationgui.h>
#include <applicationdatabase.h>

#include <utilities.h>

#include <ui/widgetmenu.h>
#include <ui/widgetabout.h>
#include <ui/widgetrecords.h>
#include <ui/widgetdrivers.h>
#include <ui/widgetoptions.h>

ApplicationGui::ApplicationGui() :
    guiSizeDefault(QVector2D(1920.0, 1080.0)),
    guiSize(QVector2D(1920.0, 1080.0)),
    guiScale(1.0),
    widgetMenu(0),
    widgetAbout(0),
    widgetRecords(0),
    widgetDrivers(0),
    widgetOptions(0),
    showWidgetMenu(true),
    showWidgetAbout(false),
    showWidgetRecords(false),
    showWidgetDrivers(false),
    showWidgetOptions(false),
    showHud(false),
    stringDriver(QString::null),
    stringSessionTime(QString::null),
    stringRunTime(QString::null),
    stringLapTime(QString::null),
    stringLstTime(QString::null),
    stringBstTime(QString::null),
    stringRecTime(QString::null),
    intFuelCurrent(0),
    intFuelMaximum(0),
    intBrakeTemperatureFrontLeft(0),
    intBrakeTemperatureFrontRight(0),
    intBrakeTemperatureRearLeft(0),
    intBrakeTemperatureRearRight(0),
    intTireWearFrontLeft(0),
    intTireWearFrontRight(0),
    intTireWearRearLeft(0),
    intTireWearRearRight(0),
    intEngineRPMCurrent(0),
    intEngineRPMMaximum(0),
    intEngineRPMPercentage(0),
    intEngineOilTemperature(0),
    intEngineWaterTemperature(0),
    boolEngineOverheating(false),
    stringGear(QString::null),
    intSpeed(0),
    boolSpeedLimiterActive(false) {
    // initialize GUI size depending on desktop size
    const QRect rectDesktop = QApplication::desktop()->screenGeometry();
    guiSize = QVector2D(rectDesktop.width(), rectDesktop.height());
    // initialize GUI scale depending on desktop size compared to default desktop size
    const float scaleWidth = (float)(guiSize.x()) / (float)(guiSizeDefault.x());
    const float scaleHeight = (float)(guiSize.y()) / (float)(guiSizeDefault.y());
    guiScale = scaleWidth <= scaleHeight ? scaleWidth : scaleHeight;
    // update both properties
    setGuiSize(guiSize);
    setGuiScale(guiScale);
    // initialize fonts
    initializeFonts();
    // initialize widgets
    initializeWidgets();
    // update widgets
    updateWidgets();
}

ApplicationGui::~ApplicationGui() {
    // TODO/FIXME: fore some reasons this leads to a crash
    //deinitializeWidgets();
}

ApplicationGui &ApplicationGui::instance() {
    static ApplicationGui applicationGui;
    return applicationGui;
}

void ApplicationGui::initializeFonts() {
    const int fontId = QFontDatabase::addApplicationFont(":/fonts/FONT_BITWISE");
    const QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    guiFontXL = QFont(fontFamily, 32 * guiScale);
    guiFontL = QFont(fontFamily, 24 * guiScale);
    guiFontM = QFont(fontFamily, 16 * guiScale);
    guiFontS = QFont(fontFamily, 12 * guiScale);
}

void ApplicationGui::initializeWidgets() {
    // menu widget
    const int widgetMenuX = 14 * guiScale;
    const int widgetMenuY = 43 * guiScale;
    const int widgetMenuW = 32 * guiScale;
    const int widgetMenuH = 945 * guiScale;
    const QRect widgetMenuRect(widgetMenuX, widgetMenuY, widgetMenuW, widgetMenuH);
    widgetMenu = new WidgetMenu(guiScale, guiFontXL, guiFontL, guiFontM, guiFontS);
    widgetMenu->setGeometry(widgetMenuRect);
    // about widget
    const int widgetAboutX = 60 * guiScale;
    const int widgetAboutY = 43 * guiScale;
    const int widgetAboutW = 878 * guiScale;
    const int widgetAboutH = 945 * guiScale;
    const QRect widgetAboutRect(widgetAboutX, widgetAboutY, widgetAboutW, widgetAboutH);
    widgetAbout = new WidgetAbout(guiScale, guiFontXL, guiFontL, guiFontM, guiFontS);
    widgetAbout->setGeometry(widgetAboutRect);
    // records widget
    const int widgetRecordsX = 60 * guiScale;
    const int widgetRecordsY = 43 * guiScale;
    const int widgetRecordsW = 878 * guiScale;
    const int widgetRecordsH = 945 * guiScale;
    const QRect widgetRecordsRect(widgetRecordsX, widgetRecordsY, widgetRecordsW, widgetRecordsH);
    widgetRecords = new WidgetRecords(guiScale, guiFontXL, guiFontL, guiFontM, guiFontS);
    widgetRecords->setGeometry(widgetRecordsRect);
    // drivers widget
    const int widgetDriversX = 60 * guiScale;
    const int widgetDriversY = 43 * guiScale;
    const int widgetDriversW = 878 * guiScale;
    const int widgetDriversH = 945 * guiScale;
    const QRect widgetDriversRect(widgetDriversX, widgetDriversY, widgetDriversW, widgetDriversH);
    widgetDrivers = new WidgetDrivers(guiScale, guiFontXL, guiFontL, guiFontM, guiFontS);
    widgetDrivers->setGeometry(widgetDriversRect);
    // options widget
    const int widgetOptionsX = 60 * guiScale;
    const int widgetOptionsY = 43 * guiScale;
    const int widgetOptionsW = 878 * guiScale;
    const int widgetOptionsH = 945 * guiScale;
    const QRect widgetOptionsRect(widgetOptionsX, widgetOptionsY, widgetOptionsW, widgetOptionsH);
    widgetOptions = new WidgetOptions(guiScale, guiFontXL, guiFontL, guiFontM, guiFontS);
    widgetOptions->setGeometry(widgetOptionsRect);
    // connect signals and slots
    connect(widgetMenu, SIGNAL(signalPressedButtonAbout(Qt::MouseButton)), this, SLOT(slotWidgetMenuPressedButtonAbout(Qt::MouseButton)));
    connect(widgetMenu, SIGNAL(signalPressedButtonRecords(Qt::MouseButton)), this, SLOT(slotWidgetMenuPressedButtonRecords(Qt::MouseButton)));
    connect(widgetMenu, SIGNAL(signalPressedButtonDrivers(Qt::MouseButton)), this, SLOT(slotWidgetMenuPressedButtonDrivers(Qt::MouseButton)));
    connect(widgetMenu, SIGNAL(signalPressedButtonOptions(Qt::MouseButton)), this, SLOT(slotWidgetMenuPressedButtonOptions(Qt::MouseButton)));
    connect(widgetMenu, SIGNAL(signalPressedButtonQuit(Qt::MouseButton)), this, SLOT(slotWidgetMenuPressedButtonQuit(Qt::MouseButton)));
}

void ApplicationGui::deinitializeWidgets() {
    // disconnect signals and slots
    disconnect(widgetMenu, SIGNAL(signalPressedButtonAbout(Qt::MouseButton)), this, SLOT(slotWidgetMenuPressedButtonAbout(Qt::MouseButton)));
    disconnect(widgetMenu, SIGNAL(signalPressedButtonRecords(Qt::MouseButton)), this, SLOT(slotWidgetMenuPressedButtonRecords(Qt::MouseButton)));
    disconnect(widgetMenu, SIGNAL(signalPressedButtonDrivers(Qt::MouseButton)), this, SLOT(slotWidgetMenuPressedButtonDrivers(Qt::MouseButton)));
    disconnect(widgetMenu, SIGNAL(signalPressedButtonOptions(Qt::MouseButton)), this, SLOT(slotWidgetMenuPressedButtonOptions(Qt::MouseButton)));
    disconnect(widgetMenu, SIGNAL(signalPressedButtonQuit(Qt::MouseButton)), this, SLOT(slotWidgetMenuPressedButtonQuit(Qt::MouseButton)));
    // delete widgets
    delete widgetMenu;
    delete widgetAbout;
    delete widgetRecords;
    delete widgetDrivers;
    delete widgetOptions;
}

void ApplicationGui::updateWidgets() {
    // show/hide widgets
    widgetMenu->setVisible(getShowWidgetMenu());
    widgetAbout->setVisible(getShowWidgetAbout());
    widgetRecords->setVisible(getShowWidgetRecords());
    widgetDrivers->setVisible(getShowWidgetDrivers());
    widgetOptions->setVisible(getShowWidgetOptions());
    // update widgets if necessary
    if(getShowWidgetMenu()) widgetMenu->update();
    if(getShowWidgetAbout()) widgetAbout->update();
    if(getShowWidgetRecords()) widgetRecords->update();
    if(getShowWidgetDrivers()) widgetDrivers->update();
    if(getShowWidgetOptions()) widgetOptions->update();
}

void ApplicationGui::slotReceivedClientServerMessage(const ClientServerMessage &_message) {
    // process individual messages filtered by type
    switch(_message.m_type) {
    case CLIENT_SERVER_MESSAGE_TYPE_START_SESSION:
        processMessageStartSession(_message);
        break;
    case CLIENT_SERVER_MESSAGE_TYPE_FINISH_SESSION:
        processMessageFinishSession(_message);
        break;
    case CLIENT_SERVER_MESSAGE_TYPE_START_RUN:
        processMessageStartRun(_message);
        break;
    case CLIENT_SERVER_MESSAGE_TYPE_FINISH_RUN:
        processMessageFinishRun(_message);
        break;
    case CLIENT_SERVER_MESSAGE_TYPE_UPDATE_TELEMETRY:
        processMessageUpdateTelemetry(_message);
        break;
    default:
        break;
    }
}

void ApplicationGui::processMessageStartSession(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_START_SESSION) return;
    setShowWidgetMenu(true);
    setShowWidgetAbout(false);
    setShowWidgetRecords(false);
    setShowWidgetDrivers(false);
    setShowWidgetOptions(false);
    updateWidgets();
    setShowHud(false);
}

void ApplicationGui::processMessageFinishSession(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_FINISH_SESSION) return;
    setShowWidgetMenu(true);
    setShowWidgetAbout(false);
    setShowWidgetRecords(false);
    setShowWidgetDrivers(false);
    setShowWidgetOptions(false);
    updateWidgets();
    setShowHud(false);
}

void ApplicationGui::processMessageStartRun(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_START_RUN) return;
    setShowWidgetMenu(false);
    setShowWidgetAbout(false);
    setShowWidgetRecords(false);
    setShowWidgetDrivers(false);
    setShowWidgetOptions(false);
    updateWidgets();
}

void ApplicationGui::processMessageFinishRun(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_FINISH_RUN) return;
    setShowWidgetMenu(true);
    setShowWidgetAbout(false);
    setShowWidgetRecords(false);
    setShowWidgetDrivers(false);
    setShowWidgetOptions(false);
    updateWidgets();
    setShowHud(false);
}

void ApplicationGui::processMessageUpdateTelemetry(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_UPDATE_TELEMETRY) return;
    // acquire current driver, current session, current run, and current lap
    const Driver *driver = ApplicationDatabase::instance().getCurrentDriver();
    const Session *session = ApplicationDatabase::instance().getCurrentSession();
    const Run *run = ApplicationDatabase::instance().getCurrentRun();
    const Lap *lap = ApplicationDatabase::instance().getCurrentLap();
    // the current lap may be invalid, but if any of the other variables
    // is invalid, we hide the HUD and return without doing anything else
    if(!driver || !session || !run) {
        setShowHud(false);
        return;
    }
    // at this point it's safe to show the HUD
    setShowHud(true);
    // calculate session time, run time, and lap time as well as lst time, bst time, and rec time
    const int64_t localTime = Utilities::Core::getMillisecondsSinceEpoch();
    const int64_t localSessionTime = localTime - session->timeStart;
    const int64_t localRunTime = localTime - run->timeStart;
    const int64_t localLapTime = lap ? lap->time : 0;
    const int64_t localLstTime = 0;
    const int64_t localBstTime = 0;
    const int64_t localRecTime = 0;
    // set properties
    setStringDriver(driver->name);
    setStringSessionTime(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localSessionTime));
    setStringRunTime(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localRunTime));
    setStringLapTime(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localLapTime));
    setStringLstTime(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localLstTime));
    setStringBstTime(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localBstTime));
    setStringRecTime(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localRecTime));
    setIntFuelCurrent((int)(_message.m_fuelCurrent));
    setIntFuelMaximum((int)(_message.m_fuelMaximum));
    setIntBrakeTemperatureFrontLeft((int)(_message.m_brakeTemperature[0]));
    setIntBrakeTemperatureFrontRight((int)(_message.m_brakeTemperature[1]));
    setIntBrakeTemperatureRearLeft((int)(_message.m_brakeTemperature[2]));
    setIntBrakeTemperatureRearRight((int)(_message.m_brakeTemperature[3]));
    setIntTireWearFrontLeft(_message.m_tireFlat[0] ? 0 : (int)(_message.m_tireWear[0] * 100.0));
    setIntTireWearFrontRight(_message.m_tireFlat[1] ? 0 : (int)(_message.m_tireWear[1] * 100.0));
    setIntTireWearRearLeft(_message.m_tireFlat[2] ? 0 : (int)(_message.m_tireWear[2] * 100.0));
    setIntTireWearRearRight(_message.m_tireFlat[3] ? 0 : (int)(_message.m_tireWear[3] * 100.0));
    setIntEngineRPMCurrent((int)(_message.m_engineRPMCurrent));
    setIntEngineRPMMaximum((int)(_message.m_engineRPMMaximum));
    setIntEngineRPMPercentage((int)(_message.m_engineRPMCurrent / _message.m_engineRPMMaximum * 100.0));
    setIntEngineOilTemperature((int)(_message.m_engineOilTemperature));
    setIntEngineWaterTemperature((int)(_message.m_engineWaterTemperature));
    setBoolEngineOverheating(_message.m_engineOverheating);
    setStringGear(_message.m_gearCurrent == -1 ? "R" : _message.m_gearCurrent == 0 ? "N" : QString::number(_message.m_gearCurrent));
    setIntSpeed((int)(_message.m_speed * 3.6));
    setBoolSpeedLimiterActive(_message.m_speedLimiterActive);
}

void ApplicationGui::update() {
    widgetMenu->update();
    widgetAbout->update();
    widgetRecords->update();
    widgetDrivers->update();
    widgetOptions->update();
}

void ApplicationGui::slotWidgetMenuPressedButtonAbout(const Qt::MouseButton _mouseButton) {
    if(_mouseButton == Qt::LeftButton) {
        const bool visibleAbout = getShowWidgetAbout();
        setShowWidgetMenu(true);
        setShowWidgetAbout(!visibleAbout);
        setShowWidgetRecords(false);
        setShowWidgetDrivers(false);
        setShowWidgetOptions(false);
        updateWidgets();
    }
}

void ApplicationGui::slotWidgetMenuPressedButtonRecords(const Qt::MouseButton _mouseButton) {
    if(_mouseButton == Qt::LeftButton) {
        const bool visibleRecords = getShowWidgetRecords();
        setShowWidgetMenu(true);
        setShowWidgetAbout(false);
        setShowWidgetRecords(!visibleRecords);
        setShowWidgetDrivers(false);
        setShowWidgetOptions(false);
        updateWidgets();
    }
}

void ApplicationGui::slotWidgetMenuPressedButtonDrivers(const Qt::MouseButton _mouseButton) {
    if(_mouseButton == Qt::LeftButton) {
        const bool visibleDrivers = getShowWidgetDrivers();
        setShowWidgetMenu(true);
        setShowWidgetAbout(false);
        setShowWidgetRecords(false);
        setShowWidgetDrivers(!visibleDrivers);
        setShowWidgetOptions(false);
        updateWidgets();
    }
}

void ApplicationGui::slotWidgetMenuPressedButtonOptions(const Qt::MouseButton _mouseButton) {
    if(_mouseButton == Qt::LeftButton) {
        const bool visibleOptions = getShowWidgetOptions();
        setShowWidgetMenu(true);
        setShowWidgetAbout(false);
        setShowWidgetRecords(false);
        setShowWidgetDrivers(false);
        setShowWidgetOptions(!visibleOptions);
        updateWidgets();
    }
}

void ApplicationGui::slotWidgetMenuPressedButtonQuit(const Qt::MouseButton _mouseButton) {
    if(_mouseButton == Qt::LeftButton) {
        qApp->quit();
    }
}
