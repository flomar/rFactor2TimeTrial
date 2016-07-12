// applicationdatabase.cpp

#include <applicationdatabase.h>
#include <application.h>

SqlRelationalTableModel::SqlRelationalTableModel(QObject *_parent) :
    QSqlRelationalTableModel(_parent) {

}

SqlRelationalTableModel::~SqlRelationalTableModel() {

}

QHash<int, QByteArray> SqlRelationalTableModel::roleNames() const {
    QHash<int, QByteArray> hashRoleNames = QSqlRelationalTableModel::roleNames();
    for(int indexColumn=0; indexColumn<columnCount(); indexColumn++) {
        hashRoleNames[Qt::UserRole + indexColumn + 1] = headerData(indexColumn, Qt::Horizontal).toByteArray();
    }
    return hashRoleNames;
}

QVariant SqlRelationalTableModel::data(const QModelIndex &_index, int _role) const {
    if(_index.row() >= rowCount()) {
        return QVariant(QString::null);
    }
    else if(_role < Qt::UserRole) {
        return QSqlRelationalTableModel::data(_index, _role);
    }
    else {
        for(int indexColumn=0; indexColumn<columnCount(); indexColumn++) {
            if(relation(indexColumn).isValid()) {
                return record(_index.row()).value(QString(roleNames().value(_role)));
            }
        }
    }
    return QSqlRelationalTableModel::data(index(_index.row(), _role - Qt::UserRole - 1));
}

ApplicationDatabase::ApplicationDatabase(Application *_application) :
    QObject(_application),
    application(_application),
    modelOptions(0),
    modelDrivers(0),
    modelSessions(0),
    modelRuns(0),
    modelLaps(0),
    modelRecords(0),
    lapTimeLast(0),
    lapTimePersonalBest(0),
    lapTimeAbsoluteBest(0),
    initializedLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest(false),
    lnc(0),
    lno(0),
    lns(0),
    lnsThreshold(5000) {
    // connect signals and slots
    connect(this, SIGNAL(signalSelectCurrentDriver(qint64)), this, SLOT(slotSelectCurrentDriver(qint64)));
    connect(this, SIGNAL(signalCreateDriver(QString)), this, SLOT(slotCreateDriver(QString)));
    connect(this, SIGNAL(signalDeleteDriver(qint64)), this, SLOT(slotDeleteDriver(qint64)));
    connect(this, SIGNAL(signalUpdateDrivers()), this, SLOT(slotUpdateDrivers()));
    connect(this, SIGNAL(signalDeleteRecord(qint64)), this, SLOT(slotDeleteRecord(qint64)));
    connect(this, SIGNAL(signalUpdateRecords(bool,bool,bool)), this, SLOT(slotUpdateRecords(bool,bool,bool)));
}

ApplicationDatabase::~ApplicationDatabase() {
    // disconnect signals and slots
    disconnect(this, SIGNAL(signalSelectCurrentDriver(qint64)), this, SLOT(slotSelectCurrentDriver(qint64)));
    disconnect(this, SIGNAL(signalCreateDriver(QString)), this, SLOT(slotCreateDriver(QString)));
    disconnect(this, SIGNAL(signalDeleteDriver(qint64)), this, SLOT(slotDeleteDriver(qint64)));
    disconnect(this, SIGNAL(signalUpdateDrivers()), this, SLOT(slotUpdateDrivers()));
    disconnect(this, SIGNAL(signalDeleteRecord(qint64)), this, SLOT(slotDeleteRecord(qint64)));
    disconnect(this, SIGNAL(signalUpdateRecords(bool,bool,bool)), this, SLOT(slotUpdateRecords(bool,bool,bool)));
}

bool ApplicationDatabase::open(const QString &_fileName) {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(_fileName);
    if(!database.open()) return false;
    // create models (NOTE: derived, non-standard-Qt class)
    if(!modelOptions) modelOptions = new SqlRelationalTableModel(this);
    if(!modelDrivers) modelDrivers = new SqlRelationalTableModel(this);
    if(!modelSessions) modelSessions = new SqlRelationalTableModel(this);
    if(!modelRuns) modelRuns = new SqlRelationalTableModel(this);
    if(!modelLaps) modelLaps = new SqlRelationalTableModel(this);
    if(!modelRecords) modelRecords = new SqlRelationalTableModel(this);
    // initialize models
    modelOptions->setTable("Options");
    modelDrivers->setTable("Drivers");
    modelSessions->setTable("Sessions");
    modelRuns->setTable("Runs");
    modelLaps->setTable("Laps");
    modelRecords->setTable("Records");
    // select models
    if(!modelOptions->select()) return false;
    if(!modelDrivers->select()) return false;
    if(!modelSessions->select()) return false;
    if(!modelRuns->select()) return false;
    if(!modelLaps->select()) return false;
    if(!modelRecords->select()) return false;
    return true;
}

bool ApplicationDatabase::close() {
    sanitize();
    database.close();
    return true;
}

void ApplicationDatabase::sanitize() {
    // find all runs with laps
    QSet<qint64> setIdentifiersRunsWithLaps;
    for(int indexRowLap=0; indexRowLap<modelLaps->rowCount(); indexRowLap++) {
        const QSqlRecord recordLap = modelLaps->record(indexRowLap);
        const QVariantMap lap = Utilities::Database::convertSqlRecordToVariantMap(recordLap);
        setIdentifiersRunsWithLaps.insert(lap.value("IdentifierRun").toLongLong());
    }
    // find all runs without laps
    QSet<qint64> setIdentifiersRunsWithoutLaps;
    for(int indexRowRun=0; indexRowRun<modelRuns->rowCount(); indexRowRun++) {
        const QSqlRecord recordRun = modelRuns->record(indexRowRun);
        const QVariantMap run = Utilities::Database::convertSqlRecordToVariantMap(recordRun);
        if(!setIdentifiersRunsWithLaps.contains(run.value("Identifier").toLongLong())) {
            setIdentifiersRunsWithoutLaps.insert(run.value("Identifier").toLongLong());
        }
    }
    // remove all runs without laps
    foreach(const qint64 identifierRun, setIdentifiersRunsWithoutLaps.values()) {
        Utilities::Database::removeRecord(modelRuns, identifierRun);
    }
    // find all sessions with runs
    QSet<qint64> setIdentifiersSessionsWithRuns;
    for(int indexRowRun=0; indexRowRun<modelRuns->rowCount(); indexRowRun++) {
        const QSqlRecord recordRun = modelRuns->record(indexRowRun);
        const QVariantMap run = Utilities::Database::convertSqlRecordToVariantMap(recordRun);
        setIdentifiersSessionsWithRuns.insert(run.value("IdentifierSession").toLongLong());
    }
    // find all sessions without runs
    QSet<qint64> setIdentifiersSessionsWithoutRuns;
    for(int indexRowSession=0; indexRowSession<modelSessions->rowCount(); indexRowSession++) {
        const QSqlRecord recordSession = modelSessions->record(indexRowSession);
        const QVariantMap session = Utilities::Database::convertSqlRecordToVariantMap(recordSession);
        if(!setIdentifiersSessionsWithRuns.contains(session.value("Identifier").toLongLong())) {
            setIdentifiersSessionsWithoutRuns.insert(session.value("Identifier").toLongLong());
        }
    }
    // remove all sessions without runs
    foreach(const qint64 identifierSession, setIdentifiersSessionsWithoutRuns.values()) {
        Utilities::Database::removeRecord(modelSessions, identifierSession);
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
    QVariantMap newSession;
    newSession.insert("Identifier", Utilities::Database::createSmallestAvailableIdentifier(modelSessions));
    newSession.insert("TimeStart", Utilities::Core::getMillisecondsSinceEpoch());
    newSession.insert("TimeFinish", 0);
    newSession.insert("NameTrack", QString(QString::null));
    newSession.insert("NameCar", QString(QString::null));
    // write new session to database (Identifier, TimeStart, TimeFinish, NameTrack, NameCar)
    Utilities::Database::addRecord(modelSessions, Utilities::Database::convertVariantMapToSqlRecord(newSession, QStringList() << "Identifier" << "TimeStart" << "TimeFinish" << "NameTrack" << "NameCar"));
    // reset variables
    setCurrentDriver(QVariantMap());
    setCurrentSession(newSession);
    setCurrentRun(QVariantMap());
    setCurrentLap(QVariantMap());
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
    if(!currentSession.isEmpty()) {
        // update current session
        currentSession.insert("TimeFinish", Utilities::Core::getMillisecondsSinceEpoch());
        // update current session in database (Identifier, TimeStart, TimeFinish, NameTrack, NameCar)
        Utilities::Database::setRecord(modelSessions, Utilities::Database::convertVariantMapToSqlRecord(currentSession, QStringList() << "Identifier" << "TimeStart" << "TimeFinish" << "NameTrack" << "NameCar"));
        // reset variables
        setCurrentDriver(QVariantMap());
        setCurrentSession(QVariantMap());
        setCurrentRun(QVariantMap());
        setCurrentLap(QVariantMap());
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
    if(!currentDriver.isEmpty() && !currentSession.isEmpty()) {
        // create new run
        QVariantMap newRun;
        newRun.insert("Identifier", Utilities::Database::createSmallestAvailableIdentifier(modelRuns));
        newRun.insert("IdentifierDriver", currentDriver.value("Identifier").toLongLong());
        newRun.insert("IdentifierSession", currentSession.value("Identifier").toLongLong());
        newRun.insert("TimeStart", Utilities::Core::getMillisecondsSinceEpoch());
        newRun.insert("TimeFinish", 0);
        newRun.insert("NameFrontTireCompound", QString(QString::null));
        newRun.insert("NameRearTireCompound", QString(QString::null));
        // write new run to database (Identifier, IdentifierDriver, IdentifierSession, TimeStart, TimeFinish, NameFrontTireCompound, NameRearTireCompound)
        Utilities::Database::addRecord(modelRuns, Utilities::Database::convertVariantMapToSqlRecord(newRun, QStringList() << "Identifier" << "IdentifierDriver" << "IdentifierSession" << "TimeStart" << "TimeFinish" << "NameFrontTireCompound" << "NameRearTireCompound"));
        // reset variables
        setCurrentRun(newRun);
        setCurrentLap(QVariantMap());
        // reset internal variables
        initializedLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest = false;
    }
    // emit signal to other internal components
    emit signalReceivedClientServerMessage(_message);
}

void ApplicationDatabase::processMessageFinishRun(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_FINISH_RUN) return;
    // we need a valid run
    if(!currentRun.isEmpty()) {
        // update current run
        currentRun.insert("TimeFinish", Utilities::Core::getMillisecondsSinceEpoch());
        // update current run in database (Identifier, IdentifierDriver, IdentifierSession, TimeStart, TimeFinish, NameFrontTireCompound, NameRearTireCompound)
        Utilities::Database::setRecord(modelRuns, Utilities::Database::convertVariantMapToSqlRecord(currentRun, QStringList() << "Identifier" << "IdentifierDriver" << "IdentifierSession" << "TimeStart" << "TimeFinish" << "NameFrontTireCompound" << "NameRearTireCompound"));
        // reset variables
        setCurrentRun(QVariantMap());
        setCurrentLap(QVariantMap());
    }
    // emit signal to other internal components
    emit signalReceivedClientServerMessage(_message);
}

void ApplicationDatabase::processMessageUpdateTelemetry(const ClientServerMessage &_message) {
    if(_message.m_type != CLIENT_SERVER_MESSAGE_TYPE_UPDATE_TELEMETRY) return;
    // acquire data from the message (session-specific)
    if(!currentSession.isEmpty()) {
        const QString nameTrack = _message.m_nameTrack;
        const QString nameCar = _message.m_nameCar;
        if(!nameTrack.isEmpty() && nameTrack != currentSession.value("NameTrack").toString() && !nameCar.isEmpty() && nameCar != currentSession.value("NameCar").toString()) {
            // update current session
            currentSession.insert("NameTrack", nameTrack);
            currentSession.insert("NameCar", nameCar);
            // update current session in database (Identifier, TimeStart, TimeFinish, NameTrack, NameCar)
            Utilities::Database::setRecord(modelSessions, Utilities::Database::convertVariantMapToSqlRecord(currentSession, QStringList() << "Identifier" << "TimeStart" << "TimeFinish" << "NameTrack" << "NameCar"));
        }
    }
    // acquire data from the message (run-specific)
    if(!currentRun.isEmpty()) {
        const QString nameFrontTireCompound = _message.m_nameFrontTireCompound;
        const QString nameRearTireCompound = _message.m_nameRearTireCompound;
        if(!nameFrontTireCompound.isEmpty() && nameFrontTireCompound != currentRun.value("NameFrontTireCompound").toString() && !nameRearTireCompound.isEmpty() && nameRearTireCompound != currentRun.value("NameRearTireCompound").toString()) {
            // update current run
            currentRun.insert("NameFrontTireCompound", nameFrontTireCompound);
            currentRun.insert("NameRearTireCompound", nameRearTireCompound);
            // update current run in database (Identifier, IdentifierDriver, IdentifierSession, TimeStart, TimeFinish, NameFrontTireCompound, NameRearTireCompound)
            Utilities::Database::setRecord(modelRuns, Utilities::Database::convertVariantMapToSqlRecord(currentRun, QStringList() << "Identifier" << "IdentifierDriver" << "IdentifierSession" << "TimeStart" << "TimeFinish" << "NameFrontTireCompound" << "NameRearTireCompound"));
        }
    }
    // we need a valid session and a valid run
    if(!currentSession.isEmpty() && !currentRun.isEmpty()) {
        // IMPORTANT: initializing the following does not work unless
        // we have a valid session and a valid run, but it should be
        // called only once (the control variable is reset to false
        // whenever a new run is started)
        if(!initializedLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest) {
            initializeLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest();
            initializedLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest = true;
        }
        // do some magic with internal variables to find out
        // when exactly a lap has been started; see header
        // file for some more explanation
        const qint64 now = Utilities::Core::getMillisecondsSinceEpoch();
        lnc = _message.m_lapNumber;
        if(lnc > lno) {
            lns = 0;
            if(now - currentRun.value("TimeStart").toLongLong() > lnsThreshold) {
                lns = lnc;
            }
            lno = lnc;
        }
        // acquire data from the message
        const qint64 elapsedTime = _message.m_elapsedTime;
        const qint64 elapsedTimeLapStart = _message.m_elapsedTimeLapStart;
        // check whether a new lap has been started (without an already existing one)
        if(currentLap.isEmpty() && lns == lnc && lns != 0) {
            // create new lap
            QVariantMap newLap;
            newLap.insert("Identifier", Utilities::Database::createSmallestAvailableIdentifier(modelLaps));
            newLap.insert("IdentifierRun", currentRun.value("Identifier").toLongLong());
            newLap.insert("ElapsedTimeStart", elapsedTimeLapStart);
            // update current lap
            currentLap = newLap;
        }
        // check whether a new lap has been started (with an already existing one)
        else if(!currentLap.isEmpty() && elapsedTimeLapStart != currentLap.value("ElapsedTimeStart").toLongLong()) {
            // update current lap
            currentLap.insert("ElapsedTimeFinish", elapsedTimeLapStart);
            currentLap.insert("Time", elapsedTimeLapStart - currentLap.value("ElapsedTimeStart").toLongLong());
            // write current lap to database (Identifier, IdentifierRun, Time)
            Utilities::Database::addRecord(modelLaps, Utilities::Database::convertVariantMapToSqlRecord(currentLap, QStringList() << "Identifier" << "IdentifierRun" << "Time"));
            // create new record
            QVariantMap newRecord;
            newRecord.insert("Identifier", Utilities::Database::createSmallestAvailableIdentifier(modelRecords));
            newRecord.insert("IdentifierDriver", currentDriver.value("Identifier").toLongLong());
            newRecord.insert("IdentifierSession", currentSession.value("Identifier").toLongLong());
            newRecord.insert("IdentifierRun", currentRun.value("Identifier").toLongLong());
            newRecord.insert("IdentifierLap", currentLap.value("Identifier").toLongLong());
            newRecord.insert("Time", currentLap.value("Time").toLongLong());
            newRecord.insert("Date", now);
            newRecord.insert("TimeHumanReadable", Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(currentLap.value("Time").toLongLong()));
            newRecord.insert("DateHumanReadable", Utilities::Core::timeInMillisecondsToStringDate(now));
            newRecord.insert("NameDriver", currentDriver.value("Name").toString());
            newRecord.insert("NameTrack", currentSession.value("NameTrack").toString());
            newRecord.insert("NameCar", currentSession.value("NameCar").toString());
            newRecord.insert("NameFrontTireCompound", currentRun.value("NameFrontTireCompound").toString());
            newRecord.insert("NameRearTireCompound", currentRun.value("NameRearTireCompound").toString());
            // write new record to database (Identifier, IdentifierDriver, IdentifierSession, IdentifierRun, IdentifierLap, Time, Date, TimeHumanReadable, DateHumanReadable, NameDriver, NameTrack, NameCar, NameFrontTireCompound, NameRearTireCompound)
            Utilities::Database::addRecord(modelRecords, Utilities::Database::convertVariantMapToSqlRecord(newRecord, QStringList() << "Identifier" << "IdentifierDriver" << "IdentifierSession" << "IdentifierRun" << "IdentifierLap" << "Time" << "Date" << "TimeHumanReadable" << "DateHumanReadable" << "NameDriver" << "NameTrack" << "NameCar" << "NameFrontTireCompound" << "NameRearTireCompound"));
            // update last lap time, personal best lap time, and absolute best lap time in the HUD
            updateLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest(currentLap);
            // create new lap
            QVariantMap newLap;
            newLap.insert("Identifier", Utilities::Database::createSmallestAvailableIdentifier(modelLaps));
            newLap.insert("IdentifierRun", currentRun.value("Identifier").toLongLong());
            newLap.insert("ElapsedTimeStart", elapsedTimeLapStart);
            // update current lap
            currentLap = newLap;
        }
        // update an existing lap
        else if(!currentLap.isEmpty()) {
            currentLap.insert("ElapsedTime", elapsedTime);
            currentLap.insert("Time", currentLap.value("ElapsedTime").toLongLong() - currentLap.value("ElapsedTimeStart").toLongLong());
        }
    }
    // emit signal to other internal components
    emit signalReceivedClientServerMessage(_message);
}

void ApplicationDatabase::slotSelectCurrentDriver(const qint64 _identifierCurrentDriver) {
    if(!_identifierCurrentDriver) return;
    const QVariantMap selectedCurrentDriver = Utilities::Database::convertSqlRecordToVariantMap(Utilities::Database::getRecord(modelDrivers, _identifierCurrentDriver));
    if(selectedCurrentDriver.isEmpty()) return;
    setCurrentDriver(selectedCurrentDriver);
}

void ApplicationDatabase::slotCreateDriver(const QString &_nameDriver) {
    // don't allow empty driver names
    if(_nameDriver.isEmpty()) return;
    // don't allow duplicate driver names
    for(int indexRow=0; indexRow<modelDrivers->rowCount(); indexRow++) {
        const QSqlRecord recordDriver = modelDrivers->record(indexRow);
        if(recordDriver.value("Name").toString() == _nameDriver) {
            return;
        }
    }
    // create new driver
    QVariantMap newDriver;
    newDriver.insert("Identifier", Utilities::Database::createSmallestAvailableIdentifier(modelDrivers));
    newDriver.insert("Name", _nameDriver);
    // write new driver to database (Identifier, Name)
    Utilities::Database::addRecord(modelDrivers, Utilities::Database::convertVariantMapToSqlRecord(newDriver, QStringList() << "Identifier" << "Name"));
    modelDrivers->select();
}

void ApplicationDatabase::slotDeleteDriver(const qint64 _identifierDriver) {
    // collect all runs, laps, and records associated with the specified driver
    QVector<qint64> vectorIdentifiersRuns;
    QVector<qint64> vectorIdentifiersLaps;
    QVector<qint64> vectorIdentifiersRecords;
    for(int indexRowRun=0; indexRowRun<modelRuns->rowCount(); indexRowRun++) {
        const QSqlRecord recordRun = modelRuns->record(indexRowRun);
        const QVariantMap run = Utilities::Database::convertSqlRecordToVariantMap(recordRun);
        if(run.value("IdentifierDriver").toLongLong() == _identifierDriver) {
            vectorIdentifiersRuns.append(run.value("Identifier").toLongLong());
        }
    }
    for(int indexRowLap=0; indexRowLap<modelLaps->rowCount(); indexRowLap++) {
        const QSqlRecord recordLap = modelLaps->record(indexRowLap);
        const QVariantMap lap = Utilities::Database::convertSqlRecordToVariantMap(recordLap);
        if(vectorIdentifiersRuns.contains(lap.value("IdentifierRun").toLongLong())) {
            vectorIdentifiersLaps.append(lap.value("Identifier").toLongLong());
        }
    }
    for(int indexRowRecord=0; indexRowRecord<modelRecords->rowCount(); indexRowRecord++) {
        const QSqlRecord recordRecord = modelRecords->record(indexRowRecord);
        const QVariantMap record = Utilities::Database::convertSqlRecordToVariantMap(recordRecord);
        if(vectorIdentifiersLaps.contains(record.value("IdentifierLap").toLongLong())) {
            vectorIdentifiersRecords.append(record.value("Identifier").toLongLong());
        }
    }
    // delete records, laps, runs, and the driver
    foreach(const qint64 identifierRecord, vectorIdentifiersRecords) {
        Utilities::Database::removeRecord(modelRecords, identifierRecord);
    }
    foreach(const qint64 identifierRun, vectorIdentifiersRuns) {
        Utilities::Database::removeRecord(modelRuns, identifierRun);
    }
    foreach(const qint64 identifierLap, vectorIdentifiersLaps) {
        Utilities::Database::removeRecord(modelLaps, identifierLap);
    }
    Utilities::Database::removeRecord(modelDrivers, _identifierDriver);
}

void ApplicationDatabase::slotUpdateDrivers() {
    modelDrivers->select();
}

void ApplicationDatabase::slotDeleteRecord(const qint64 _identifierRecord) {
    // delete not only the record itself, but also the lap associated with it
    for(int indexRowRecord=0; indexRowRecord<modelRecords->rowCount(); indexRowRecord++) {
        const QSqlRecord recordRecord = modelRecords->record(indexRowRecord);
        const QVariantMap record = Utilities::Database::convertSqlRecordToVariantMap(recordRecord);
        if(record.value("Identifier").toLongLong() == _identifierRecord) {
            // delete the record
            Utilities::Database::removeRecord(modelRecords, record.value("Identifier").toLongLong());
            // delete the lap
            Utilities::Database::removeRecord(modelLaps, record.value("IdentifierLap").toLongLong());
        }
    }
}

void ApplicationDatabase::slotUpdateRecords(const bool _showOnlyCurrentDriver, const bool _showOnlyCurrentTrack, const bool _showOnlyCurrentCar) {
    // this slot is invoked from the outside to update the records to be displayed; based
    // on the input parameters, we either show all records or only those pertaining to the
    // current driver, the current track, or the current car, respectively; if the variables
    // for current driver or current session (which holds the track and the car) are invalid,
    // the corresponding input parameters are ignored and no filtering is applied
    QString stringFilter = QString::null;
    QString stringFilterDriver = QString::null;
    QString stringFilterTrack = QString::null;
    QString stringFilterCar = QString::null;
    // try to create filter for current driver
    if(!currentDriver.isEmpty() && _showOnlyCurrentDriver) {
        stringFilterDriver.append(QString("NameDriver='%1'").arg(currentDriver.value("Name").toString()));
    }
    // try to create filter for current track
    if(!currentSession.isEmpty() && !currentSession.value("NameTrack").toString().isEmpty() && _showOnlyCurrentTrack) {
        stringFilterTrack.append(QString("NameTrack='%1'").arg(currentSession.value("NameTrack").toString()));
    }
    // try to create filter for current car
    if(!currentSession.isEmpty() && !currentSession.value("NameCar").toString().isEmpty() && _showOnlyCurrentCar) {
        stringFilterCar.append(QString("NameCar='%1'").arg(currentSession.value("NameCar").toString()));
    }
    // construct final filter
    if(!stringFilterDriver.isEmpty()) {
        stringFilter.append(stringFilterDriver);
    }
    if(!stringFilterTrack.isEmpty()) {
        if(stringFilter.isEmpty()) stringFilter.append(stringFilterTrack);
        else stringFilter.append(QString(" AND ") + stringFilterTrack);
    }
    if(!stringFilterCar.isEmpty()) {
        if(stringFilter.isEmpty()) stringFilter.append(stringFilterCar);
        else stringFilter.append(QString(" AND " ) + stringFilterCar);
    }
    // apply the filter, and then sort and re-select the model
    modelRecords->setFilter(stringFilter);
    modelRecords->setSort(modelRecords->fieldIndex("Time"), Qt::AscendingOrder);
    modelRecords->select();
}

void ApplicationDatabase::initializeLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest() {
    // initialize variables to default values
    lapTimeLast = 0;
    lapTimePersonalBest = 0;
    lapTimeAbsoluteBest = 0;
    // acquire the personal best lap time (for the current driver)
    // and the absolute best lap time (for any driver)
    getLapTimePersonalBestAndLapTimeAbsoluteBest(lapTimePersonalBest, lapTimeAbsoluteBest);
}

void ApplicationDatabase::updateLapTimeLastAndLapTimePersonalBestAndLapTimeAbsoluteBest(const QVariantMap &_lap) {
    // update times for last lap, personal best lap, and absolute best lap
    const qint64 lapTime = _lap.value("Time").toLongLong();
    lapTimeLast = lapTime;
    lapTimePersonalBest = lapTimePersonalBest == 0 ? lapTime : lapTime < lapTimePersonalBest ? lapTime : lapTimePersonalBest;
    lapTimeAbsoluteBest = lapTimeAbsoluteBest == 0 ? lapTime : lapTime < lapTimeAbsoluteBest ? lapTime : lapTimeAbsoluteBest;
    // these variables will be signaled to the outside
    const bool isPersonalBest = lapTimePersonalBest && lapTimePersonalBest >= lapTime;
    const bool isAbsoluteBest = lapTimeAbsoluteBest && lapTimeAbsoluteBest >= lapTime;
    const QString infoLapTime = Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(lapTime);
    const QString infoLapTimePersonalBest = isPersonalBest ? "PERSONAL BEST" : "+" + Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(qAbs(lapTime - lapTimePersonalBest)) + " " + "[PER]";
    const QString infoLapTimeAbsoluteBest = isAbsoluteBest ? "ABSOLUTE BEST" : "+" + Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(qAbs(lapTime - lapTimeAbsoluteBest)) + " " + "[ABS]";
    // emit signal to the HUD
    emit signalLapInformation(isPersonalBest, isAbsoluteBest, infoLapTime, infoLapTimePersonalBest, infoLapTimeAbsoluteBest);
}

void ApplicationDatabase::getLapTimePersonalBestAndLapTimeAbsoluteBest(qint64 &_lapTimePersonalBest, qint64 &_lapTimeAbsoluteBest) {
    // we need valid variables for the current driver, the current session, and the current run
    if(currentDriver.isEmpty()) return;
    if(currentSession.isEmpty()) return;
    if(currentRun.isEmpty()) return;
    // initialize result variables
    _lapTimePersonalBest = 0;
    _lapTimeAbsoluteBest = 0;
    // manually update the records model, but don't apply any filtering (sorting is applied implicitly)
    emit signalUpdateRecords(false, false, false);
    // now go through the model and extract what we need
    for(int indexRowRecord=0; indexRowRecord<modelRecords->rowCount(); indexRowRecord++) {
        const QSqlRecord recordRecord = modelRecords->record(indexRowRecord);
        const QVariantMap record = Utilities::Database::convertSqlRecordToVariantMap(recordRecord);
        if(_lapTimePersonalBest == 0) {
            if(record.value("NameDriver").toString() == currentDriver.value("Name").toString()) {
                if(record.value("NameTrack").toString() == currentSession.value("NameTrack").toString()) {
                    if(record.value("NameCar").toString() == currentSession.value("NameCar").toString()) {
                        _lapTimePersonalBest = record.value("Time").toLongLong();
                    }
                }
            }
        }
        if(_lapTimeAbsoluteBest == 0) {
            if(record.value("NameTrack").toString() == currentSession.value("NameTrack").toString()) {
                if(record.value("NameCar").toString() == currentSession.value("NameCar").toString()) {
                    _lapTimeAbsoluteBest = record.value("Time").toLongLong();
                }
            }
        }
    }
}
