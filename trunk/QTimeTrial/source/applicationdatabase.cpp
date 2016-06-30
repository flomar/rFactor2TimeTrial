// applicationdatabase.cpp

#include <applicationdatabase.h>

#include <utilities.h>

ApplicationDatabase::ApplicationDatabase() :
    currentDriver(0),
    currentSession(0),
    currentRun(0),
    currentLap(0),
    lnc(0),
    lno(0),
    lns(0),
    lnsThreshold(5000) {

}

ApplicationDatabase::~ApplicationDatabase() {

}

ApplicationDatabase &ApplicationDatabase::instance() {
    static ApplicationDatabase applicationDatabase;
    return applicationDatabase;
}

bool ApplicationDatabase::open(const QString &_fileName) {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(_fileName);
    if(!database.open()) return false;
    // clear existing data
    deleteData();
    // read data
    if(!readOptions()) return false;
    if(!readDrivers()) return false;
    if(!readSessions()) return false;
    if(!readRuns()) return false;
    if(!readLaps()) return false;
    return true;
}

bool ApplicationDatabase::close() {
    // depending on the options we need to do some special stuff
    // before actually writing the database
    autoDeleteSessionsAndRunsAndLaps();
    // write data
    if(!writeOptions()) return false;
    if(!writeDrivers()) return false;
    if(!writeSessions()) return false;
    if(!writeRuns()) return false;
    if(!writeLaps()) return false;
    database.close();
    return true;
}

bool ApplicationDatabase::readOptions() {
    QSqlQuery query("SELECT * FROM Options");
    while(query.next()) {
        if(!query.isValid()) return false;
        Options *options = new Options;
        QSqlRecord record = query.record();
        options->identifier = record.value("Identifier").toLongLong();
        options->autoDeleteSessions = record.value("AutoDeleteSessions").toLongLong();
        options->autoDeleteRuns = record.value("AutoDeleteRuns").toLongLong();
        options->autoDeleteLaps = record.value("AutoDeleteLaps").toLongLong();
        mapOptions.insert(options->identifier, options);
    }
    return true;
}

bool ApplicationDatabase::readDrivers() {
    QSqlQuery query("SELECT * FROM Drivers");
    while(query.next()) {
        if(!query.isValid()) return false;
        Driver *driver = new Driver;
        QSqlRecord record = query.record();
        driver->identifier = record.value("Identifier").toLongLong();
        driver->name = record.value("Name").toString();
        mapDrivers.insert(driver->identifier, driver);
    }
    return true;
}

bool ApplicationDatabase::readSessions() {
    QSqlQuery query("SELECT * FROM Sessions");
    while(query.next()) {
        if(!query.isValid()) return false;
        Session *session = new Session;
        QSqlRecord record = query.record();
        session->identifier = record.value("Identifier").toLongLong();
        session->timeStart = record.value("TimeStart").toLongLong();
        session->timeFinish = record.value("TimeFinish").toLongLong();
        session->nameTrack = record.value("NameTrack").toString();
        session->nameCar = record.value("NameCar").toString();
        mapSessions.insert(session->identifier, session);
    }
    return true;
}

bool ApplicationDatabase::readRuns() {
    QSqlQuery query("SELECT * FROM Runs");
    while(query.next()) {
        if(!query.isValid()) return false;
        Run *run = new Run;
        QSqlRecord record = query.record();
        run->identifier = record.value("Identifier").toLongLong();
        run->identifierDriver = record.value("IdentifierDriver").toLongLong();
        run->identifierSession = record.value("IdentifierSession").toLongLong();
        run->timeStart = record.value("TimeStart").toLongLong();
        run->timeFinish = record.value("TimeFinish").toLongLong();
        run->nameFrontTireCompound = record.value("NameFrontTireCompound").toString();
        run->nameRearTireCompound = record.value("NameRearTireCompound").toString();
        mapRuns.insert(run->identifier, run);
    }
    return true;
}

bool ApplicationDatabase::readLaps() {
    QSqlQuery query("SELECT * FROM Laps");
    while(query.next()) {
        if(!query.isValid()) return false;
        Lap *lap = new Lap;
        QSqlRecord record = query.record();
        lap->identifier = record.value("Identifier").toLongLong();
        lap->identifierRun = record.value("IdentifierRun").toLongLong();
        lap->time = record.value("Time").toLongLong();
        mapLaps.insert(lap->identifier, lap);
    }
    return true;
}

bool ApplicationDatabase::writeOptions() const {
    QSqlQuery queryDelete;
    if(!queryDelete.exec("DELETE FROM Options"))
        return false;
    for(QMap<int64_t, Options*>::const_iterator iter=mapOptions.begin(); iter!=mapOptions.end(); iter++) {
        const Options *options = iter.value();
        if(!options) return false;
        QSqlQuery query;
        query.prepare("INSERT INTO Options(Identifier, AutoDeleteSessions, AutoDeleteRuns, AutoDeleteLaps) VALUES(:identifier, :autoDeleteSessions, :autoDeleteRuns, :autoDeleteLaps)");
        query.bindValue(":identifier", QVariant::fromValue(options->identifier));
        query.bindValue(":autoDeleteSessions", QVariant::fromValue(options->autoDeleteSessions));
        query.bindValue(":autoDeleteRuns", QVariant::fromValue(options->autoDeleteRuns));
        query.bindValue(":autoDeleteLaps", QVariant::fromValue(options->autoDeleteLaps));
        if(!query.exec())
            return false;
    }
    return true;
}

bool ApplicationDatabase::writeDrivers() const {
    QSqlQuery queryDelete;
    if(!queryDelete.exec("DELETE FROM Drivers"))
        return false;
    for(QMap<int64_t, Driver*>::const_iterator iter=mapDrivers.begin(); iter!=mapDrivers.end(); iter++) {
        const Driver *driver = iter.value();
        if(!driver) return false;
        QSqlQuery query;
        query.prepare("INSERT INTO Drivers(Identifier, Name) VALUES(:identifier, :name)");
        query.bindValue(":identifier", QVariant::fromValue(driver->identifier));
        query.bindValue(":name", driver->name);
        if(!query.exec())
            return false;
    }
    return true;
}

bool ApplicationDatabase::writeSessions() const {
    QSqlQuery queryDelete;
    if(!queryDelete.exec("DELETE FROM Sessions"))
        return false;
    for(QMap<int64_t, Session*>::const_iterator iter=mapSessions.begin(); iter!=mapSessions.end(); iter++) {
        const Session *session = iter.value();
        QSqlQuery query;
        query.prepare("INSERT INTO Sessions(Identifier, TimeStart, TimeFinish, NameTrack, NameCar) VALUES(:identifier, :timeStart, :timeFinish, :nameTrack, :nameCar)");
        query.bindValue(":identifier", QVariant::fromValue(session->identifier));
        query.bindValue(":timeStart", QVariant::fromValue(session->timeStart));
        query.bindValue(":timeFinish", QVariant::fromValue(session->timeFinish));
        query.bindValue(":nameTrack", session->nameTrack);
        query.bindValue(":nameCar", session->nameCar);
        if(!query.exec())
            return false;
    }
    return true;
}

bool ApplicationDatabase::writeRuns() const {
    QSqlQuery queryDelete;
    if(!queryDelete.exec("DELETE FROM Runs"))
        return false;
    for(QMap<int64_t, Run*>::const_iterator iter=mapRuns.begin(); iter!=mapRuns.end(); iter++) {
        const Run *run = iter.value();
        QSqlQuery query;
        query.prepare("INSERT INTO Runs(Identifier, IdentifierDriver, IdentifierSession, TimeStart, TimeFinish, NameFrontTireCompound, NameRearTireCompound) VALUES(:identifier, :identifierDriver, :identifierSession, :timeStart, :timeFinish, :nameFrontTireCompound, :nameRearTireCompound)");
        query.bindValue(":identifier", QVariant::fromValue(run->identifier));
        query.bindValue(":identifierDriver", QVariant::fromValue(run->identifierDriver));
        query.bindValue(":identifierSession", QVariant::fromValue(run->identifierSession));
        query.bindValue(":timeStart", QVariant::fromValue(run->timeStart));
        query.bindValue(":timeFinish", QVariant::fromValue(run->timeFinish));
        query.bindValue(":nameFrontTireCompound", run->nameFrontTireCompound);
        query.bindValue(":nameRearTireCompound", run->nameRearTireCompound);
        if(!query.exec())
            return false;
    }
    return true;
}

bool ApplicationDatabase::writeLaps() const {
    QSqlQuery queryDelete;
    if(!queryDelete.exec("DELETE FROM Laps"))
        return false;
    for(QMap<int64_t, Lap*>::const_iterator iter=mapLaps.begin(); iter!=mapLaps.end(); iter++) {
        const Lap *lap = iter.value();
        QSqlQuery query;
        query.prepare("INSERT INTO Laps(Identifier, IdentifierRun, Time) VALUES(:identifier, :identifierRun, :time)");
        query.bindValue(":identifier", QVariant::fromValue(lap->identifier));
        query.bindValue(":identifierRun", QVariant::fromValue(lap->identifierRun));
        query.bindValue(":time", QVariant::fromValue(lap->time));
        if(!query.exec())
            return false;
    }
    return true;
}

void ApplicationDatabase::deleteData() {
    for(QMap<int64_t, Driver*>::const_iterator iter=mapDrivers.begin(); iter!=mapDrivers.end(); iter++) {
        const Driver *driver = iter.value();
        delete driver;
    }
    for(QMap<int64_t, Session*>::const_iterator iter=mapSessions.begin(); iter!=mapSessions.end(); iter++) {
        const Session *session = iter.value();
        delete session;
    }
    for(QMap<int64_t, Run*>::const_iterator iter=mapRuns.begin(); iter!=mapRuns.end(); iter++) {
        const Run *run = iter.value();
        delete run;
    }
    for(QMap<int64_t, Lap*>::const_iterator iter=mapLaps.begin(); iter!=mapLaps.end(); iter++) {
        const Lap *lap = iter.value();
        delete lap;
    }
    mapDrivers.clear();
    mapSessions.clear();
    mapRuns.clear();
    mapLaps.clear();
}

void ApplicationDatabase::autoDeleteSessionsAndRunsAndLaps() {
    // the order of execution is important here: first we need to
    // auto-delete the laps, then the runs, and then the sessions,
    // otherwise unwanted artifacts may remain in the database
    if(!mapOptions.isEmpty()) {
        const Options *options = mapOptions.values().first();
        if(options) {
            // auto-delete laps: for every run, keep only the very best lap
            if(options->autoDeleteLaps == 1) {
                autoDeleteLaps();
            }
            // auto-delete runs: for every session, keep only non-empty runs
            if(options->autoDeleteRuns == 1) {
                autoDeleteRuns();
            }
            // auto-delete sessions: keep only non-empty sessions
            if(options->autoDeleteSessions == 1) {
                autoDeleteSessions();
            }
        }
    }
}

void ApplicationDatabase::autoDeleteSessions() {
    QVector<Session*> vectorSessionsEmpty;
    foreach(Session *session, mapSessions.values()) {
        if(session) {
            bool empty = true;
            foreach(Run *run, mapRuns.values()) {
                if(run) {
                    if(run->identifierSession == session->identifier) {
                        empty = false;
                    }
                }
            }
            if(empty) {
                vectorSessionsEmpty.push_back(session);
            }
        }
    }
    foreach(Session *session, vectorSessionsEmpty) {
        if(session) {
            mapSessions.remove(session->identifier);
            delete session;
        }
    }
}

void ApplicationDatabase::autoDeleteRuns() {
    QVector<Run*> vectorRunsEmpty;
    foreach(Run *run, mapRuns.values()) {
        if(run) {
            bool empty = true;
            foreach(Lap *lap, mapLaps.values()) {
                if(lap) {
                    if(lap->identifierRun == run->identifier) {
                        empty = false;
                    }
                }
            }
            if(empty) {
                vectorRunsEmpty.push_back(run);
            }
        }
    }
    foreach(Run *run, vectorRunsEmpty) {
        if(run) {
            mapRuns.remove(run->identifier);
            delete run;
        }
    }
}

void ApplicationDatabase::autoDeleteLaps() {
    QVector<Lap*> vectorLaps;
    QVector<Lap*> vectorLapsToBeDeleted;
    foreach(Run *run, mapRuns.values()) {
        if(run) {
            foreach(Lap *lap, mapLaps.values()) {
                if(lap) {
                    if(lap->identifierRun == run->identifier) {
                        vectorLaps.push_back(lap);
                    }
                }
            }
            qSort(vectorLaps.begin(), vectorLaps.end(), Lap::lessThanPointers);
            vectorLaps.pop_front();
            foreach(Lap *lap, vectorLaps) {
                if(lap) {
                    vectorLapsToBeDeleted.push_back(lap);
                }
            }
            vectorLaps.clear();
        }
    }
    foreach(Lap *lap, vectorLapsToBeDeleted) {
        if(lap) {
            mapLaps.remove(lap->identifier);
            delete lap;
        }
    }
}

void ApplicationDatabase::slotReceivedClientServerMessage(const ClientServerMessage &_message) {
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

void ApplicationDatabase::processMessageStartSession(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_START_SESSION) return;
    // create new session
    Session *session = new Session();
    session->identifier = Utilities::Containers::getSmallestAvailableIdentifier<int64_t, Session>(mapSessions);
    session->timeStart = Utilities::Core::getMillisecondsSinceEpoch();
    // add session to the database
    mapSessions.insert(session->identifier, session);
    // temporarily store current session
    currentSession = session;
    // reset variables
    currentDriver = 0;
    currentRun = 0;
    currentLap = 0;
    // reset internal variables
    lnc = 0;
    lno = 0;
    lns = 0;
    // emit signal to other internal components
    emit signalReceivedClientServerMessage(_message);
}

void ApplicationDatabase::processMessageFinishSession(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_FINISH_SESSION) return;
    // we need a valid session
    if(currentSession) {
        // update current session
        currentSession->timeFinish = Utilities::Core::getMillisecondsSinceEpoch();
        // delete current lap if necessary
        delete currentLap;
        // reset variables
        currentDriver = 0;
        currentSession = 0;
        currentRun = 0;
        currentLap = 0;
        // reset internal variables
        lnc = 0;
        lno = 0;
        lns = 0;
    }
    // emit signal to other internal components
    emit signalReceivedClientServerMessage(_message);
}

void ApplicationDatabase::processMessageStartRun(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_START_RUN) return;
    // we need a valid driver and a valid session
    if(currentDriver && currentSession) {
        // create new run
        Run *run = new Run();
        run->identifier = Utilities::Containers::getSmallestAvailableIdentifier<int64_t, Run>(mapRuns);
        run->identifierDriver = currentDriver->identifier;
        run->identifierSession = currentSession->identifier;
        run->timeStart = Utilities::Core::getMillisecondsSinceEpoch();
        // add run to the database
        mapRuns.insert(run->identifier, run);
        // temporarily store current run
        currentRun = run;
        // reset variables
        currentLap = 0;
    }
    // emit signal to other internal components
    emit signalReceivedClientServerMessage(_message);
}

void ApplicationDatabase::processMessageFinishRun(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_FINISH_RUN) return;
    // we need a valid run
    if(currentRun) {
        // update current run
        currentRun->timeFinish = Utilities::Core::getMillisecondsSinceEpoch();
        // delete current lap if necessary
        delete currentLap;
        // reset variables
        currentRun = 0;
        currentLap = 0;
    }
    // emit signal to other internal components
    emit signalReceivedClientServerMessage(_message);
}

void ApplicationDatabase::processMessageUpdateTelemetry(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_UPDATE_TELEMETRY) return;
    // acquire data from the message
    if(currentSession) {
        const QString nameTrackNew = _message.m_nameTrack;
        const QString nameCarNew = _message.m_nameCar;
        if(!nameTrackNew.isEmpty() && nameTrackNew != currentSession->nameTrack)
            currentSession->nameTrack = nameTrackNew;
        if(!nameCarNew.isEmpty() && nameCarNew != currentSession->nameCar)
            currentSession->nameCar = nameCarNew;
    }
    // acquire data from the message
    if(currentRun) {
        const QString nameFrontTireCompoundNew = _message.m_nameFrontTireCompound;
        const QString nameRearTireCompoundNew = _message.m_nameRearTireCompound;
        if(!nameFrontTireCompoundNew.isEmpty() && nameFrontTireCompoundNew != currentRun->nameFrontTireCompound)
            currentRun->nameFrontTireCompound = nameFrontTireCompoundNew;
        if(!nameRearTireCompoundNew.isEmpty() && nameRearTireCompoundNew != currentRun->nameRearTireCompound)
            currentRun->nameRearTireCompound = nameRearTireCompoundNew;
    }
    // we need a valid session and a valid run
    if(currentSession && currentRun) {
        // do some magic with internal variables to find out
        // when exactly a lap has been started; see header
        // file for some more explanation
        const int64_t now = Utilities::Core::getMillisecondsSinceEpoch();
        lnc = _message.m_lapNumber;
        if(lnc > lno) {
            lns = 0;
            if(now - currentRun->timeStart > lnsThreshold) {
                lns = lnc;
            }
            lno = lnc;
        }
        // acquire data from the message
        const qint64 elapsedTime = _message.m_elapsedTime;
        const qint64 elapsedTimeLapStart = _message.m_elapsedTimeLapStart;
        // check whether a new lap has been started (without an already existing one)
        if(!currentLap && lns == lnc && lns != 0) {
            // create a new lap
            Lap *lap = new Lap();
            lap->identifier = Utilities::Containers::getSmallestAvailableIdentifier<int64_t, Lap>(mapLaps);
            lap->identifierRun = currentRun->identifier;
            lap->elapsedTime = elapsedTime;
            lap->elapsedTimeStart = elapsedTimeLapStart;
            lap->time = lap->elapsedTime - lap->elapsedTimeStart;
            currentLap = lap;
        }
        // check whether a new lap has been started (with an already existing one)
        else if(currentLap && elapsedTimeLapStart != currentLap->elapsedTimeStart) {
            // add lap to the database
            currentLap->elapsedTimeFinish = elapsedTimeLapStart;
            currentLap->time = currentLap->elapsedTimeFinish - currentLap->elapsedTimeStart;
            mapLaps.insert(currentLap->identifier, currentLap);
            // display lap information in the HUD
            displayLapInformation(currentLap);
            // create a new lap
            Lap *lap = new Lap();
            lap->identifier = Utilities::Containers::getSmallestAvailableIdentifier<int64_t, Lap>(mapLaps);
            lap->identifierRun = currentRun->identifier;
            lap->elapsedTime = elapsedTime;
            lap->elapsedTimeStart = elapsedTimeLapStart;
            lap->time = lap->elapsedTime - lap->elapsedTimeStart;
            currentLap = lap;
        }
        // update an existing lap
        else if(currentLap) {
            currentLap->elapsedTime = elapsedTime;
            currentLap->time = currentLap->elapsedTime - currentLap->elapsedTimeStart;
        }
    }
    // emit signal to other internal components
    emit signalReceivedClientServerMessage(_message);
}

void ApplicationDatabase::setCurrentDriver(const QString &_name) {
    for(QMap<int64_t, Driver*>::const_iterator iter=mapDrivers.begin(); iter!=mapDrivers.end(); iter++) {
        Driver *driver = iter.value();
        if(driver) {
            if(driver->name == _name) {
                currentDriver = driver;
            }
        }
    }
}

QString ApplicationDatabase::getCurrentTrackName() const {
    QString trackName;
    if(currentSession) {
        if(!currentSession->nameTrack.isEmpty()) {
            trackName = currentSession->nameTrack;
        }
    }
    return trackName;
}

QVector<Record> ApplicationDatabase::getVectorRecordsUnsortedAndUnfiltered() const {
    QVector<Record> vectorRecords;
    for(QMap<int64_t, Lap*>::const_iterator iter=mapLaps.begin(); iter!=mapLaps.end(); iter++) {
        Lap *lap = iter.value();
        if(lap) {
            Run *run = mapRuns.value(lap->identifierRun);
            if(run) {
                Driver *driver = mapDrivers.value(run->identifierDriver);
                Session *session = mapSessions.value(run->identifierSession);
                if(driver && session) {
                    Record record;
                    record.time = lap->time;
                    record.date = run->timeFinish;
                    record.track = session->nameTrack;
                    record.driver = driver->name;
                    record.car = session->nameCar;
                    record.frontTireCompound = run->nameFrontTireCompound;
                    record.rearTireCompound = run->nameRearTireCompound;
                    vectorRecords.push_back(record);
                }
            }
        }
    }
    return vectorRecords;
}

void ApplicationDatabase::displayLapInformation(const Lap *_lap) const {
    // acquire both the absolute record and the personal record (if existing)
    Record recordAbsolute;
    Record recordPersonal;
    getAbsoluteRecordAndPersonalRecord(_lap, recordAbsolute, recordPersonal);
    // extract the lap time
    const QString infoLapTime = Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(_lap->time);
    // acquire absolute values
    bool absoluteBest = false;
    QString infoAbsolute = QString::null;
    if(recordAbsolute.time == -1) {
        absoluteBest = true;
        infoAbsolute = "ABSOLUTE BEST";
    }
    else {
        const qint64 absoluteDeltaTime = recordAbsolute.time - _lap->time;
        absoluteBest = absoluteDeltaTime >= 0;
        infoAbsolute = absoluteBest ? "ABSOLUTE BEST" : "+" + Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(qAbs(absoluteDeltaTime));
    }
    // acquire personal values
    bool personalBest = false;
    QString infoPersonal = QString::null;
    if(recordPersonal.time == -1) {
        personalBest = true;
        infoPersonal = "PERSONAL BEST";
    }
    else {
        const qint64 personalDeltaTime = recordPersonal.time - _lap->time;
        personalBest = personalDeltaTime >= 0;
        infoPersonal = personalBest ? "PERSONAL BEST" : "+" + Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(qAbs(personalDeltaTime));
    }
    // emit signal to the HUD
    emit signalLapInformation(infoLapTime, infoAbsolute, infoPersonal, absoluteBest, personalBest);
}

void ApplicationDatabase::getAbsoluteRecordAndPersonalRecord(const Lap *_lap, Record &_recordAbsolute, Record &_recordPersonal) const {
    // acquire specified lap, specified run, specified session, and specified driver
    const Lap *specifiedLap = _lap;
    if(!specifiedLap) return;
    const Run *specifiedRun = mapRuns.value(specifiedLap->identifierRun);
    if(!specifiedRun) return;
    const Session *specifiedSession = mapSessions.value(specifiedRun->identifierSession);
    if(!specifiedSession) return;
    const Driver *specifiedDriver = mapDrivers.value(specifiedRun->identifierDriver);
    if(!specifiedDriver) return;
    // the following is required to detect non-existing records
    _recordAbsolute.time = -1;
    _recordPersonal.time = -1;
    // go through all available laps and extract all records
    // fitting the specified criteria
    QVector<Record> vectorRecords;
    for(QMap<int64_t, Lap*>::const_iterator iter=mapLaps.begin(); iter!=mapLaps.end(); iter++) {
        Lap *lap = iter.value();
        if(lap) {
            Run *run = mapRuns.value(lap->identifierRun);
            if(run) {
                // ignore runs with the wrong criteria
                if(run->nameFrontTireCompound != specifiedRun->nameFrontTireCompound) continue;
                if(run->nameRearTireCompound != specifiedRun->nameRearTireCompound) continue;
                Driver *driver = mapDrivers.value(run->identifierDriver);
                Session *session = mapSessions.value(run->identifierSession);
                if(driver && session) {
                    // ignore sessions with the wrong criteria
                    if(session->nameTrack != specifiedSession->nameTrack) continue;
                    if(session->nameCar != specifiedSession->nameCar) continue;
                    // if we reach this point, we have a valid record
                    // with regards to the specified criteria
                    Record record;
                    record.time = lap->time;
                    record.track = session->nameTrack;
                    record.driver = driver->name;
                    record.car = session->nameCar;
                    record.frontTireCompound = run->nameFrontTireCompound;
                    record.rearTireCompound = run->nameRearTireCompound;
                    vectorRecords.push_back(record);
                }
            }
        }
    }
    // sort the records
    qSort(vectorRecords.begin(), vectorRecords.end(), Record::lessThan);
    // extract absolute best record (if any)
    if(!vectorRecords.isEmpty()) {
        _recordAbsolute = vectorRecords.first();
    }
    // extract personal best record (if any)
    foreach(const Record record, vectorRecords) {
        if(record.driver == specifiedDriver->name) {
            _recordPersonal = record;
            break;
        }
    }
}

bool ApplicationDatabase::createDriver(const QString &_name) {
    // don't allow empty driver names
    if(_name.isEmpty()) {
        return false;
    }
    // don't allow duplicate driver names
    foreach(const Driver *driver, mapDrivers.values()) {
        if(driver) {
            if(driver->name == _name) {
                return false;
            }
        }
    }
    // create a new driver, and add it to the database
    Driver *driver = new Driver();
    driver->identifier = Utilities::Containers::getSmallestAvailableIdentifier<qint64, Driver>(mapDrivers);
    driver->name = _name;
    mapDrivers.insert(driver->identifier, driver);
    return true;
}

bool ApplicationDatabase::deleteDriver(const QString &_name) {
    foreach(const Driver *driver, mapDrivers.values()) {
        if(driver) {
            if(driver->name == _name) {
                mapDrivers.remove(driver->identifier);
                delete driver;
                return true;
            }
        }
    }
    return false;
}
