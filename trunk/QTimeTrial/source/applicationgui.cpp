// applicationgui.cpp

#include <applicationgui.h>
#include <application.h>

ApplicationGui::ApplicationGui(Application *_application) :
    QObject(_application),
    application(_application),
    guiSizeDefault(QVector2D(1920.0, 1080.0)),
    guiSize(QVector2D(1920.0, 1080.0)),
    guiScale(1.0),
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
    stringLapTimeLast(QString::null),
    stringLapTimePersonalBest(QString::null),
    stringLapTimeAbsoluteBest(QString::null),
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
    // initialize widgets
    initializeWidgets();
}

ApplicationGui::~ApplicationGui() {
    deinitializeWidgets();
}

void ApplicationGui::initializeWidgets() {
    // connect signals and slots
    connect(this, SIGNAL(signalWidgetMenuClickedButtonAbout()), this, SLOT(slotWidgetMenuClickedButtonAbout()));
    connect(this, SIGNAL(signalWidgetMenuClickedButtonDrivers()), this, SLOT(slotWidgetMenuClickedButtonDrivers()));
    connect(this, SIGNAL(signalWidgetMenuClickedButtonRecords()), this, SLOT(slotWidgetMenuClickedButtonRecords()));
    connect(this, SIGNAL(signalWidgetMenuClickedButtonOptions()), this, SLOT(slotWidgetMenuClickedButtonOptions()));
    connect(this, SIGNAL(signalWidgetMenuClickedButtonQuit()), this, SLOT(slotWidgetMenuClickedButtonQuit()));
}

void ApplicationGui::deinitializeWidgets() {
    // disconnect signals and slots
    disconnect(this, SIGNAL(signalWidgetMenuClickedButtonAbout()), this, SLOT(slotWidgetMenuClickedButtonAbout()));
    disconnect(this, SIGNAL(signalWidgetMenuClickedButtonDrivers()), this, SLOT(slotWidgetMenuClickedButtonDrivers()));
    disconnect(this, SIGNAL(signalWidgetMenuClickedButtonRecords()), this, SLOT(slotWidgetMenuClickedButtonRecords()));
    disconnect(this, SIGNAL(signalWidgetMenuClickedButtonOptions()), this, SLOT(slotWidgetMenuClickedButtonOptions()));
    disconnect(this, SIGNAL(signalWidgetMenuClickedButtonQuit()), this, SLOT(slotWidgetMenuClickedButtonQuit()));
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
    setShowHud(false);
}

void ApplicationGui::processMessageFinishSession(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_FINISH_SESSION) return;
    setShowWidgetMenu(true);
    setShowWidgetAbout(false);
    setShowWidgetRecords(false);
    setShowWidgetDrivers(false);
    setShowWidgetOptions(false);
    setShowHud(false);
}

void ApplicationGui::processMessageStartRun(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_START_RUN) return;
    setShowWidgetMenu(false);
    setShowWidgetAbout(false);
    setShowWidgetRecords(false);
    setShowWidgetDrivers(false);
    setShowWidgetOptions(false);
}

void ApplicationGui::processMessageFinishRun(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_FINISH_RUN) return;
    setShowWidgetMenu(true);
    setShowWidgetAbout(false);
    setShowWidgetRecords(false);
    setShowWidgetDrivers(false);
    setShowWidgetOptions(false);
    setShowHud(false);
}

void ApplicationGui::processMessageUpdateTelemetry(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_UPDATE_TELEMETRY) return;
    // acquire a pointer to the application database
    ApplicationDatabase *applicationDatabase = application->getApplicationDatabase();
    if(!applicationDatabase) return;
    // acquire current driver, current session, current run, and current lap
    const QVariantMap driver = application->getApplicationDatabase()->getCurrentDriver();
    const QVariantMap session = application->getApplicationDatabase()->getCurrentSession();
    const QVariantMap run = application->getApplicationDatabase()->getCurrentRun();
    const QVariantMap lap = application->getApplicationDatabase()->getCurrentLap();
    // the current lap may be invalid, but if any of the other variables
    // is invalid, we hide the HUD and return without doing anything else
    if(driver.isEmpty() || session.isEmpty() || run.isEmpty()) {
        setShowHud(false);
        return;
    }
    // at this point it's safe to show the HUD
    setShowHud(true);
    // calculate session time, run time, and lap time, and acquire lst time, bst time, and rec time
    const int64_t localTime = Utilities::Core::getMillisecondsSinceEpoch();
    const int64_t localSessionTime = localTime - session.value("TimeStart").toLongLong();
    const int64_t localRunTime = localTime - run.value("TimeStart").toLongLong();
    const int64_t localLapTime = lap.isEmpty() ? 0 : lap.value("Time").toLongLong();
    const int64_t localLapTimeLast = applicationDatabase->getLapTimeLast();
    const int64_t localLapTimePersonalBest = applicationDatabase->getLapTimePersonalBest();
    const int64_t localLapTimeAbsoluteBest = applicationDatabase->getLapTimeAbsoluteBest();
    // set properties
    setStringDriver(driver.value("Name").toString());
    setStringSessionTime(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localSessionTime));
    setStringRunTime(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localRunTime));
    setStringLapTime(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localLapTime));
    setStringLapTimeLast(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localLapTimeLast));
    setStringLapTimePersonalBest(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localLapTimePersonalBest));
    setStringLapTimeAbsoluteBest(Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(localLapTimeAbsoluteBest));
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

void ApplicationGui::slotWidgetMenuClickedButtonAbout() {
    const bool visibleAbout = getShowWidgetAbout();
    setShowWidgetMenu(true);
    setShowWidgetAbout(!visibleAbout);
    setShowWidgetDrivers(false);
    setShowWidgetRecords(false);
    setShowWidgetOptions(false);
}

void ApplicationGui::slotWidgetMenuClickedButtonDrivers() {
    const bool visibleDrivers = getShowWidgetDrivers();
    setShowWidgetMenu(true);
    setShowWidgetAbout(false);
    setShowWidgetDrivers(!visibleDrivers);
    setShowWidgetRecords(false);
    setShowWidgetOptions(false);
}

void ApplicationGui::slotWidgetMenuClickedButtonRecords() {
    const bool visibleRecords = getShowWidgetRecords();
    setShowWidgetMenu(true);
    setShowWidgetAbout(false);
    setShowWidgetDrivers(false);
    setShowWidgetRecords(!visibleRecords);
    setShowWidgetOptions(false);
}

void ApplicationGui::slotWidgetMenuClickedButtonOptions() {
    const bool visibleOptions = getShowWidgetOptions();
    setShowWidgetMenu(true);
    setShowWidgetAbout(false);
    setShowWidgetDrivers(false);
    setShowWidgetRecords(false);
    setShowWidgetOptions(!visibleOptions);
}

void ApplicationGui::slotWidgetMenuClickedButtonQuit() {
    qApp->quit();
}
