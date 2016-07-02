// applicationdatabase.h

#ifndef _APPLICATIONDATABASE_H_
#define _APPLICATIONDATABASE_H_

#include <main.h>

class ApplicationDatabase : public QObject {
    Q_OBJECT
protected:
    ApplicationDatabase();
    virtual ~ApplicationDatabase();
public:
    static ApplicationDatabase &instance();
public:
    bool open(const QString &_fileName);
    bool close();
private:
    bool readOptions();
    bool readDrivers();
    bool readSessions();
    bool readRuns();
    bool readLaps();
private:
    bool writeOptions() const;
    bool writeDrivers() const;
    bool writeSessions() const;
    bool writeRuns() const;
    bool writeLaps() const;
private:
    QSqlDatabase database;
private:
    void deleteData();
private:
    void autoDeleteSessionsAndRunsAndLaps();
    void autoDeleteSessions();
    void autoDeleteRuns();
    void autoDeleteLaps();
private:
    QMap<int64_t, Options*> mapOptions;
    QMap<int64_t, Driver*> mapDrivers;
    QMap<int64_t, Session*> mapSessions;
    QMap<int64_t, Run*> mapRuns;
    QMap<int64_t, Lap*> mapLaps;
public:
    const QMap<int64_t, Options*> &getMapOptions() const { return mapOptions; }
    const QMap<int64_t, Driver*> &getMapDrivers() const { return mapDrivers; }
    const QMap<int64_t, Session*> &getMapSessions() const { return mapSessions; }
    const QMap<int64_t, Run*> &getMapRuns() const { return mapRuns; }
    const QMap<int64_t, Lap*> &getMapLaps() const { return mapLaps; }
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
    Driver *currentDriver;
    Session *currentSession;
    Run *currentRun;
    Lap *currentLap;
public:
    const Driver *getCurrentDriver() const { return currentDriver; }
    const Session *getCurrentSession() const { return currentSession; }
    const Run *getCurrentRun() const { return currentRun; }
    const Lap *getCurrentLap() const { return currentLap; }
private:
    int64_t lapTimeLast;
    int64_t lapTimePersonalBest;
    int64_t lapTimeAbsoluteBest;
public:
    int64_t getLapTimeLast() const { return lapTimeLast; }
    int64_t getLapTimePersonalBest() const { return lapTimePersonalBest; }
    int64_t getLapTimeAbsoluteBest() const { return lapTimeAbsoluteBest; }
private:
    bool initializedLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest;
    void initializeLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest();
    void updateLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest(const Lap *_lap);
private:
    // for the current setup (track, car, tires), this function extracts
    // the personal best lap time (for the current driver) and the absolute
    // best lap time (for any driver); if a result value is zero, then the
    // corresponding lap time could not be extracted
    void getLapTimePersonalBestAndLapTimeAbsoluteBest(int64_t &_lapTimePersonalBest, int64_t &_lapTimeAbsoluteBest) const;
signals:
    // this signal is emitted after each finished lap to temporarily
    // display some additional information to the user in the HUD
    void signalLapInformation(const bool _isPersonalBest, const bool _isAbsoluteBest, const QString &_infoLapTime, const QString &_infoLapTimePersonalBest, const QString &_infoLapTimeAbsoluteBest);
public:
    void setCurrentDriver(const QString &_name);
public:
    QString getCurrentTrackName() const;
    QVector<Record> getVectorRecordsUnsortedAndUnfiltered() const;
public:
    bool createDriver(const QString &_name);
    bool deleteDriver(const QString &_name);
private:
    // ATTENTION: these are internal variables used to find out whether
    // a new lap has been started or not based on the "lapNumber" variable
    // we get from rF2 through telemetry updates; "lnc" represents the
    // current lap number, "lno" represents the old lap number, and "lns"
    // represents the lap number in which our calculations are started;
    // the "lnsTreshold" variable is required to cope with rF2's antics
    // of starting new laps right after the box has been left
    int64_t lnc;
    int64_t lno;
    int64_t lns;
    const int64_t lnsThreshold;
};

#endif
