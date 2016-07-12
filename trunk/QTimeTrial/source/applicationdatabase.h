// applicationdatabase.h

#ifndef _APPLICATIONDATABASE_H_
#define _APPLICATIONDATABASE_H_

#include <main.h>

class Application;

class SqlRelationalTableModel : public QSqlRelationalTableModel {
    Q_OBJECT
public:
    SqlRelationalTableModel(QObject *_parent = 0);
    virtual ~SqlRelationalTableModel();
public:
    virtual QHash<int, QByteArray> roleNames() const;
public:
    virtual QVariant data(const QModelIndex &_index, int _role) const;
};

class ApplicationDatabase : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantMap currentDriver READ getCurrentDriver WRITE setCurrentDriver NOTIFY signalChangedCurrentDriver)
    Q_PROPERTY(QVariantMap currentSession READ getCurrentSession WRITE setCurrentSession NOTIFY signalChangedCurrentSession)
    Q_PROPERTY(QVariantMap currentRun READ getCurrentRun WRITE setCurrentRun NOTIFY signalChangedCurrentRun)
    Q_PROPERTY(QVariantMap currentLap READ getCurrentLap WRITE setCurrentLap NOTIFY signalChangedCurrentLap)
public:
    ApplicationDatabase(Application *_application);
    virtual ~ApplicationDatabase();
private:
    Application *application;
public:
    bool open(const QString &_fileName);
    bool close();
private:
    void sanitize();
private:
    QSqlDatabase database;
private:
    QSqlRelationalTableModel *modelOptions;
    QSqlRelationalTableModel *modelDrivers;
    QSqlRelationalTableModel *modelSessions;
    QSqlRelationalTableModel *modelRuns;
    QSqlRelationalTableModel *modelLaps;
    QSqlRelationalTableModel *modelRecords;
public:
    QSqlRelationalTableModel *getModelOptions() { return modelOptions; }
    QSqlRelationalTableModel *getModelDrivers() { return modelDrivers; }
    QSqlRelationalTableModel *getModelSessions() { return modelSessions; }
    QSqlRelationalTableModel *getModelRuns() { return modelRuns; }
    QSqlRelationalTableModel *getModelLaps() { return modelLaps; }
    QSqlRelationalTableModel *getModelRecords() { return modelRecords; }
private slots:
    void slotReceivedClientServerMessage(const ClientServerMessage &_message);
private:
    void processMessageStartSession(const ClientServerMessage &_message);
    void processMessageFinishSession(const ClientServerMessage &_message);
    void processMessageStartRun(const ClientServerMessage &_message);
    void processMessageFinishRun(const ClientServerMessage &_message);
    void processMessageUpdateTelemetry(const ClientServerMessage &_message);
signals:
    void signalReceivedClientServerMessage(const ClientServerMessage &_message);
private:
    QVariantMap currentDriver;
    QVariantMap currentSession;
    QVariantMap currentRun;
    QVariantMap currentLap;
public:
    const QVariantMap &getCurrentDriver() const { return currentDriver; }
    const QVariantMap &getCurrentSession() const { return currentSession; }
    const QVariantMap &getCurrentRun() const { return currentRun; }
    const QVariantMap &getCurrentLap() const { return currentLap; }
public:
    void setCurrentDriver(const QVariantMap &_currentDriver) { currentDriver = _currentDriver; emit signalChangedCurrentDriver(); }
    void setCurrentSession(const QVariantMap &_currentSession) { currentSession = _currentSession; emit signalChangedCurrentSession(); }
    void setCurrentRun(const QVariantMap &_currentRun) { currentRun = _currentRun; emit signalChangedCurrentRun(); }
    void setCurrentLap(const QVariantMap &_currentLap) { currentLap = _currentLap; emit signalChangedCurrentLap(); }
signals:
    void signalChangedCurrentDriver();
    void signalChangedCurrentSession();
    void signalChangedCurrentRun();
    void signalChangedCurrentLap();
signals:
    void signalSelectCurrentDriver(const qint64 _identifierCurrentDriver);
    void signalCreateDriver(const QString &_nameDriver);
    void signalDeleteDriver(const qint64 _identifierDriver);
    void signalUpdateDrivers();
    void signalDeleteRecord(const qint64 _identifierRecord);
    void signalUpdateRecords(const bool _showOnlyCurrentDriver, const bool _showOnlyCurrentTrack, const bool _showOnlyCurrentCar);
private slots:
    void slotSelectCurrentDriver(const qint64 _identifierCurrentDriver);
    void slotCreateDriver(const QString &_nameDriver);
    void slotDeleteDriver(const qint64 _identifierDriver);
    void slotUpdateDrivers();
    void slotDeleteRecord(const qint64 _identifierRecord);
    void slotUpdateRecords(const bool _showOnlyCurrentDriver, const bool _showOnlyCurrentTrack, const bool _showOnlyCurrentCar);
private:
    qint64 lapTimeLast;
    qint64 lapTimePersonalBest;
    qint64 lapTimeAbsoluteBest;
public:
    qint64 getLapTimeLast() const { return lapTimeLast; }
    qint64 getLapTimePersonalBest() const { return lapTimePersonalBest; }
    qint64 getLapTimeAbsoluteBest() const { return lapTimeAbsoluteBest; }
private:
    bool initializedLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest;
    void initializeLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest();
    void updateLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest(const QVariantMap &_lap);
private:
    // for the current setup (track, car, tires), this function extracts
    // the personal best lap time (for the current driver) and the absolute
    // best lap time (for any driver); if a result value is zero, then the
    // corresponding lap time could not be extracted
    void getLapTimePersonalBestAndLapTimeAbsoluteBest(qint64 &_lapTimePersonalBest, qint64 &_lapTimeAbsoluteBest);
signals:
    // this signal is emitted after each finished lap to temporarily
    // display some additional information to the user in the HUD
    void signalLapInformation(const bool _isPersonalBest, const bool _isAbsoluteBest, const QString &_infoLapTime, const QString &_infoLapTimePersonalBest, const QString &_infoLapTimeAbsoluteBest);
private:
    // ATTENTION: these are internal variables used to find out whether
    // a new lap has been started or not based on the "lapNumber" variable
    // we get from rF2 through telemetry updates; "lnc" represents the
    // current lap number, "lno" represents the old lap number, and "lns"
    // represents the lap number in which our calculations are started;
    // the "lnsTreshold" variable is required to cope with rF2's antics
    // of starting new laps right after the box has been left
    qint64 lnc;
    qint64 lno;
    qint64 lns;
    const qint64 lnsThreshold;
};

#endif
