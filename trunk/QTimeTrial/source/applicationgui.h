// applicationgui.h

#ifndef _APPLICATIONGUI_H_
#define _APPLICATIONGUI_H_

#include <main.h>

class WidgetMenu;
class WidgetAbout;
class WidgetRecords;
class WidgetDrivers;
class WidgetOptions;

class ApplicationGui : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVector2D guiSize READ getGuiSize WRITE setGuiSize NOTIFY signalChangedGuiSize)
    Q_PROPERTY(float guiScale READ getGuiScale WRITE setGuiScale NOTIFY signalChangedGuiScale)
    Q_PROPERTY(bool showWidgetMenu READ getShowWidgetMenu WRITE setShowWidgetMenu NOTIFY signalChangedShowWidgetMenu)
    Q_PROPERTY(bool showWidgetAbout READ getShowWidgetAbout WRITE setShowWidgetAbout NOTIFY signalChangedShowWidgetAbout)
    Q_PROPERTY(bool showWidgetRecords READ getShowWidgetRecords WRITE setShowWidgetRecords NOTIFY signalChangedShowWidgetRecords)
    Q_PROPERTY(bool showWidgetDrivers READ getShowWidgetDrivers WRITE setShowWidgetDrivers NOTIFY signalChangedShowWidgetDrivers)
    Q_PROPERTY(bool showWidgetOptions READ getShowWidgetOptions WRITE setShowWidgetOptions NOTIFY signalChangedShowWidgetOptions)
    Q_PROPERTY(bool showHud READ getShowHud WRITE setShowHud NOTIFY signalChangedShowHud)
    // HUD properties / TELEMETRY properties
    Q_PROPERTY(QString stringDriver READ getStringDriver WRITE setStringDriver NOTIFY signalChangedStringDriver)
    Q_PROPERTY(QString stringSessionTime READ getStringSessionTime WRITE setStringSessionTime NOTIFY signalChangedStringSessionTime)
    Q_PROPERTY(QString stringRunTime READ getStringRunTime WRITE setStringRunTime NOTIFY signalChangedStringRunTime)
    Q_PROPERTY(QString stringLapTime READ getStringLapTime WRITE setStringLapTime NOTIFY signalChangedStringLapTime)
    Q_PROPERTY(QString stringLstTime READ getStringLstTime WRITE setStringLstTime NOTIFY signalChangedStringLstTime)
    Q_PROPERTY(QString stringBstTime READ getStringBstTime WRITE setStringBstTime NOTIFY signalChangedStringBstTime)
    Q_PROPERTY(QString stringRecTime READ getStringRecTime WRITE setStringRecTime NOTIFY signalChangedStringRecTime)
    Q_PROPERTY(int intFuelCurrent READ getIntFuelCurrent WRITE setIntFuelCurrent NOTIFY signalChangedIntFuelCurrent)
    Q_PROPERTY(int intFuelMaximum READ getIntFuelMaximum WRITE setIntFuelMaximum NOTIFY signalChangedIntFuelMaximum)
    Q_PROPERTY(int intBrakeTemperatureFrontLeft READ getIntBrakeTemperatureFrontLeft WRITE setIntBrakeTemperatureFrontLeft NOTIFY signalChangedIntBrakeTemperatureFrontLeft)
    Q_PROPERTY(int intBrakeTemperatureFrontRight READ getIntBrakeTemperatureFrontRight WRITE setIntBrakeTemperatureFrontRight NOTIFY signalChangedIntBrakeTemperatureFrontRight)
    Q_PROPERTY(int intBrakeTemperatureRearLeft READ getIntBrakeTemperatureRearLeft WRITE setIntBrakeTemperatureRearLeft NOTIFY signalChangedIntBrakeTemperatureRearLeft)
    Q_PROPERTY(int intBrakeTemperatureRearRight READ getIntBrakeTemperatureRearRight WRITE setIntBrakeTemperatureRearRight NOTIFY signalChangedIntBrakeTemperatureRearRight)
    Q_PROPERTY(int intTireWearFrontLeft READ getIntTireWearFrontLeft WRITE setIntTireWearFrontLeft NOTIFY signalChangedIntTireWearFrontLeft)
    Q_PROPERTY(int intTireWearFrontRight READ getIntTireWearFrontRight WRITE setIntTireWearFrontRight NOTIFY signalChangedIntTireWearFrontRight)
    Q_PROPERTY(int intTireWearRearLeft READ getIntTireWearRearLeft WRITE setIntTireWearRearLeft NOTIFY signalChangedIntTireWearRearLeft)
    Q_PROPERTY(int intTireWearRearRight READ getIntTireWearRearRight WRITE setIntTireWearRearRight NOTIFY signalChangedIntTireWearRearRight)
    Q_PROPERTY(int intEngineRPMCurrent READ getIntEngineRPMCurrent WRITE setIntEngineRPMCurrent NOTIFY signalChangedIntEngineRPMCurrent)
    Q_PROPERTY(int intEngineRPMMaximum READ getIntEngineRPMMaximum WRITE setIntEngineRPMMaximum NOTIFY signalChangedIntEngineRPMMaximum)
    Q_PROPERTY(int intEngineRPMPercentage READ getIntEngineRPMPercentage WRITE setIntEngineRPMPercentage NOTIFY signalChangedIntEngineRPMPercentage)
    Q_PROPERTY(int intEngineOilTemperature READ getIntEngineOilTemperature WRITE setIntEngineOilTemperature NOTIFY signalChangedIntEngineOilTemperature)
    Q_PROPERTY(int intEngineWaterTemperature READ getIntEngineWaterTemperature WRITE setIntEngineWaterTemperature NOTIFY signalChangedIntEngineWaterTemperature)
    Q_PROPERTY(bool boolEngineOverheating READ getBoolEngineOverheating WRITE setBoolEngineOverheating NOTIFY signalChangedBoolEngineOverheating)
    Q_PROPERTY(QString stringGear READ getStringGear WRITE setStringGear NOTIFY signalChangedStringGear)
    Q_PROPERTY(int intSpeed READ getIntSpeed WRITE setIntSpeed NOTIFY signalChangedIntSpeed)
    Q_PROPERTY(bool boolSpeedLimiterActive READ getBoolSpeedLimiterActive WRITE setBoolSpeedLimiterActive NOTIFY signalChangedBoolSpeedLimiterActive)
protected:
    ApplicationGui();
    virtual ~ApplicationGui();
public:
    static ApplicationGui &instance();
private:
    // the size this GUI is optimized for (1920x1080)
    const QVector2D guiSizeDefault;
private:
    // the actual size of this GUI: the size depends on the desktop
    // size of the user, it is initialized at application start
    QVector2D guiSize;
    // the scale of the GUI: the scale depends on the desktop size
    // of the user, it is initialized at application start; since
    // we have two dimensions, and since not all desktop sizes will
    // be exact multiples of the default GUI size, this value will
    // always represent the dimension with the smaller proportional
    // size
    float guiScale;
public:
    const QVector2D &getGuiSize() const { return guiSize; }
    float getGuiScale() const { return guiScale; }
public:
    void setGuiSize(const QVector2D &_guiSize) { guiSize = _guiSize; emit signalChangedGuiSize(); }
    void setGuiScale(const float _guiScale) { guiScale = _guiScale; emit signalChangedGuiScale(); }
signals:
    void signalChangedGuiSize();
    void signalChangedGuiScale();
private:
    // fonts depending on the GUI scale, initialized at application
    // start and injected into widgets and dialogs at construction
    QFont guiFontXL;
    QFont guiFontL;
    QFont guiFontM;
    QFont guiFontS;
private:
    void initializeFonts();
private:
    void initializeWidgets();
    void deinitializeWidgets();
private:
    void updateWidgets();
private:
    WidgetMenu *widgetMenu;
    WidgetAbout *widgetAbout;
    WidgetRecords *widgetRecords;
    WidgetDrivers *widgetDrivers;
    WidgetOptions *widgetOptions;
private slots:
    void slotReceivedClientServerMessage(const ClientServerMessage &_message);
private:
    void processMessageStartSession(const ClientServerMessage &_message);
    void processMessageFinishSession(const ClientServerMessage &_message);
    void processMessageStartRun(const ClientServerMessage &_message);
    void processMessageFinishRun(const ClientServerMessage &_message);
    void processMessageUpdateTelemetry(const ClientServerMessage &_message);
private:
    bool showWidgetMenu;
    bool showWidgetAbout;
    bool showWidgetRecords;
    bool showWidgetDrivers;
    bool showWidgetOptions;
public:
    bool getShowWidgetMenu() const { return showWidgetMenu; }
    bool getShowWidgetAbout() const { return showWidgetAbout; }
    bool getShowWidgetRecords() const { return showWidgetRecords; }
    bool getShowWidgetDrivers() const { return showWidgetDrivers; }
    bool getShowWidgetOptions() const { return showWidgetOptions; }
    void setShowWidgetMenu(const bool _showWidgetMenu) { showWidgetMenu = _showWidgetMenu; emit signalChangedShowWidgetMenu(); }
    void setShowWidgetAbout(const bool _showWidgetAbout) { showWidgetAbout = _showWidgetAbout; emit signalChangedShowWidgetAbout(); }
    void setShowWidgetRecords(const bool _showWidgetRecords) { showWidgetRecords = _showWidgetRecords; emit signalChangedShowWidgetRecords(); }
    void setShowWidgetDrivers(const bool _showWidgetDrivers) { showWidgetDrivers = _showWidgetDrivers; emit signalChangedShowWidgetDrivers(); }
    void setShowWidgetOptions(const bool _showWidgetOptions) { showWidgetOptions = _showWidgetOptions; emit signalChangedShowWidgetOptions(); }
signals:
    void signalChangedShowWidgetMenu();
    void signalChangedShowWidgetAbout();
    void signalChangedShowWidgetRecords();
    void signalChangedShowWidgetDrivers();
    void signalChangedShowWidgetOptions();
private:
    bool showHud;
public:
    bool getShowHud() const { return showHud; }
    void setShowHud(const bool _showHud) { showHud = _showHud; emit signalChangedShowHud(); }
signals:
    void signalChangedShowHud();
public:
    void update();
private slots:
    void slotWidgetMenuPressedButtonAbout(const Qt::MouseButton _mouseButton);
    void slotWidgetMenuPressedButtonRecords(const Qt::MouseButton _mouseButton);
    void slotWidgetMenuPressedButtonDrivers(const Qt::MouseButton _mouseButton);
    void slotWidgetMenuPressedButtonOptions(const Qt::MouseButton _mouseButton);
    void slotWidgetMenuPressedButtonQuit(const Qt::MouseButton _mouseButton);
private:
    QString stringDriver;
    QString stringSessionTime;
    QString stringRunTime;
    QString stringLapTime;
    QString stringLstTime;
    QString stringBstTime;
    QString stringRecTime;
    int intFuelCurrent;
    int intFuelMaximum;
    int intBrakeTemperatureFrontLeft;
    int intBrakeTemperatureFrontRight;
    int intBrakeTemperatureRearLeft;
    int intBrakeTemperatureRearRight;
    int intTireWearFrontLeft;
    int intTireWearFrontRight;
    int intTireWearRearLeft;
    int intTireWearRearRight;
    int intEngineRPMCurrent;
    int intEngineRPMMaximum;
    int intEngineRPMPercentage;
    int intEngineOilTemperature;
    int intEngineWaterTemperature;
    bool boolEngineOverheating;
    QString stringGear;
    int intSpeed;
    bool boolSpeedLimiterActive;
public:
    const QString &getStringDriver() const { return stringDriver; }
    const QString &getStringSessionTime() const { return stringSessionTime; }
    const QString &getStringRunTime() const { return stringRunTime; }
    const QString &getStringLapTime() const { return stringLapTime; }
    const QString &getStringLstTime() const { return stringLstTime; }
    const QString &getStringBstTime() const { return stringBstTime; }
    const QString &getStringRecTime() const { return stringRecTime; }
    int getIntFuelCurrent() const { return intFuelCurrent; }
    int getIntFuelMaximum() const { return intFuelMaximum; }
    int getIntBrakeTemperatureFrontLeft() const { return intBrakeTemperatureFrontLeft; }
    int getIntBrakeTemperatureFrontRight() const { return intBrakeTemperatureFrontRight; }
    int getIntBrakeTemperatureRearLeft() const { return intBrakeTemperatureRearLeft; }
    int getIntBrakeTemperatureRearRight() const { return intBrakeTemperatureRearRight; }
    int getIntTireWearFrontLeft() const { return intTireWearFrontLeft; }
    int getIntTireWearFrontRight() const { return intTireWearFrontRight; }
    int getIntTireWearRearLeft() const { return intTireWearRearLeft; }
    int getIntTireWearRearRight() const { return intTireWearRearRight; }
    int getIntEngineRPMCurrent() const { return intEngineRPMCurrent; }
    int getIntEngineRPMMaximum() const { return intEngineRPMMaximum; }
    int getIntEngineRPMPercentage() const { return intEngineRPMPercentage; }
    int getIntEngineOilTemperature() const { return intEngineOilTemperature; }
    int getIntEngineWaterTemperature() const { return intEngineWaterTemperature; }
    bool getBoolEngineOverheating() const { return boolEngineOverheating; }
    const QString &getStringGear() const { return stringGear; }
    int getIntSpeed() const { return intSpeed; }
    bool getBoolSpeedLimiterActive() const { return boolSpeedLimiterActive; }
    void setStringDriver(const QString &_stringDriver) { stringDriver = _stringDriver; emit signalChangedStringDriver(); }
    void setStringSessionTime(const QString &_stringSessionTime) { stringSessionTime = _stringSessionTime; emit signalChangedStringSessionTime(); }
    void setStringRunTime(const QString &_stringRunTime) { stringRunTime = _stringRunTime; emit signalChangedStringRunTime(); }
    void setStringLapTime(const QString &_stringLapTime) { stringLapTime = _stringLapTime; emit signalChangedStringLapTime(); }
    void setStringLstTime(const QString &_stringLstTime) { stringLstTime = _stringLstTime; emit signalChangedStringLstTime(); }
    void setStringBstTime(const QString &_stringBstTime) { stringBstTime = _stringBstTime; emit signalChangedStringBstTime(); }
    void setStringRecTime(const QString &_stringRecTime) { stringRecTime = _stringRecTime; emit signalChangedStringRecTime(); }
    void setIntFuelCurrent(const int _intFuelCurrent) { intFuelCurrent = _intFuelCurrent; emit signalChangedIntFuelCurrent(); }
    void setIntFuelMaximum(const int _intFuelMaximum) { intFuelMaximum = _intFuelMaximum; emit signalChangedIntFuelMaximum(); }
    void setIntBrakeTemperatureFrontLeft(const int _intBrakeTemperatureFrontLeft) { intBrakeTemperatureFrontLeft = _intBrakeTemperatureFrontLeft; emit signalChangedIntBrakeTemperatureFrontLeft(); }
    void setIntBrakeTemperatureFrontRight(const int _intBrakeTemperatureFrontRight) { intBrakeTemperatureFrontRight = _intBrakeTemperatureFrontRight; emit signalChangedIntBrakeTemperatureFrontRight(); }
    void setIntBrakeTemperatureRearLeft(const int _intBrakeTemperatureRearLeft) { intBrakeTemperatureRearLeft = _intBrakeTemperatureRearLeft; emit signalChangedIntBrakeTemperatureRearLeft(); }
    void setIntBrakeTemperatureRearRight(const int _intBrakeTemperatureRearRight) { intBrakeTemperatureRearRight = _intBrakeTemperatureRearRight; emit signalChangedIntBrakeTemperatureRearRight(); }
    void setIntTireWearFrontLeft(const int _intTireWearFrontLeft) { intTireWearFrontLeft = _intTireWearFrontLeft; emit signalChangedIntTireWearFrontLeft(); }
    void setIntTireWearFrontRight(const int _intTireWearFrontRight) { intTireWearFrontRight = _intTireWearFrontRight; emit signalChangedIntTireWearFrontRight(); }
    void setIntTireWearRearLeft(const int _intTireWearRearLeft) { intTireWearRearLeft = _intTireWearRearLeft; emit signalChangedIntTireWearRearLeft(); }
    void setIntTireWearRearRight(const int _intTireWearRearRight) { intTireWearRearRight = _intTireWearRearRight; emit signalChangedIntTireWearRearRight(); }
    void setIntEngineRPMCurrent(const int _intEngineRPMCurrent) { intEngineRPMCurrent = _intEngineRPMCurrent; emit signalChangedIntEngineRPMCurrent(); }
    void setIntEngineRPMMaximum(const int _intEngineRPMMaximum) { intEngineRPMMaximum = _intEngineRPMMaximum; emit signalChangedIntEngineRPMMaximum(); }
    void setIntEngineRPMPercentage(const int _intEngineRPMPercentage) { intEngineRPMPercentage = _intEngineRPMPercentage; emit signalChangedIntEngineRPMPercentage(); }
    void setIntEngineOilTemperature(const int _intEngineOilTemperature) { intEngineOilTemperature = _intEngineOilTemperature; emit signalChangedIntEngineOilTemperature(); }
    void setIntEngineWaterTemperature(const int _intEngineWaterTemperature) { intEngineWaterTemperature = _intEngineWaterTemperature; emit signalChangedIntEngineWaterTemperature(); }
    void setBoolEngineOverheating(const bool _boolEngineOverheating) { boolEngineOverheating = _boolEngineOverheating; emit signalChangedBoolEngineOverheating(); }
    void setStringGear(const QString &_stringGear) { stringGear = _stringGear; emit signalChangedStringGear(); }
    void setIntSpeed(const int _intSpeed) { intSpeed = _intSpeed; emit signalChangedIntSpeed(); }
    void setBoolSpeedLimiterActive(const bool _boolSpeedLimiterActive) { boolSpeedLimiterActive = _boolSpeedLimiterActive; emit signalChangedBoolSpeedLimiterActive(); }
signals:
    void signalChangedStringDriver();
    void signalChangedStringSessionTime();
    void signalChangedStringRunTime();
    void signalChangedStringLapTime();
    void signalChangedStringLstTime();
    void signalChangedStringBstTime();
    void signalChangedStringRecTime();
    void signalChangedIntFuelCurrent();
    void signalChangedIntFuelMaximum();
    void signalChangedIntBrakeTemperatureFrontLeft();
    void signalChangedIntBrakeTemperatureFrontRight();
    void signalChangedIntBrakeTemperatureRearLeft();
    void signalChangedIntBrakeTemperatureRearRight();
    void signalChangedIntTireWearFrontLeft();
    void signalChangedIntTireWearFrontRight();
    void signalChangedIntTireWearRearLeft();
    void signalChangedIntTireWearRearRight();
    void signalChangedIntEngineRPMCurrent();
    void signalChangedIntEngineRPMMaximum();
    void signalChangedIntEngineRPMPercentage();
    void signalChangedIntEngineOilTemperature();
    void signalChangedIntEngineWaterTemperature();
    void signalChangedBoolEngineOverheating();
    void signalChangedStringGear();
    void signalChangedIntSpeed();
    void signalChangedBoolSpeedLimiterActive();
};

#endif
