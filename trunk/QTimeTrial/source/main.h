// main.h

#ifndef _MAIN_H_
#define _MAIN_H_

#include <QDebug>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>
#include <QVector>
#include <QVector2D>
#include <QPainter>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QFont>
#include <QFontDatabase>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>

#include <stdint.h>

// include client/server protocol headers
#include "../ClientServerProtocol/clientserverprotocol.h"

struct Driver {
    Driver() : identifier(0), name(QString::null) { }
    int64_t identifier;
    QString name;
};

struct Session {
    Session() : identifier(0), timeStart(0), timeFinish(0), nameTrack(QString::null), nameCar(QString::null) { }
    int64_t identifier;
    int64_t timeStart;
    int64_t timeFinish;
    QString nameTrack;
    QString nameCar;
};

struct Run {
    Run() : identifier(0), identifierDriver(0), identifierSession(0), timeStart(0), timeFinish(0), nameFrontTireCompound(QString::null), nameRearTireCompound(QString::null) { }
    int64_t identifier;
    int64_t identifierDriver;
    int64_t identifierSession;
    int64_t timeStart;
    int64_t timeFinish;
    QString nameFrontTireCompound;
    QString nameRearTireCompound;
};

struct Lap {
    Lap() : identifier(0), identifierRun(0), time(0), elapsedTime(0), elapsedTimeStart(0), elapsedTimeFinish(0) { }
    int64_t identifier;
    int64_t identifierRun;
    int64_t time;
    int64_t elapsedTime;
    int64_t elapsedTimeStart;
    int64_t elapsedTimeFinish;
};

struct Record {
    Record() : rank(0), time(0), track(QString::null), driver(QString::null), car(QString::null), frontTireCompound(QString::null), rearTireCompound(QString::null), timeHumandReadable(QString::null) { }
    int64_t rank;
    int64_t time;
    QString track;
    QString driver;
    QString car;
    QString frontTireCompound;
    QString rearTireCompound;
    QString timeHumandReadable;
    // operator used for sorting
    static bool lessThan(const Record &_recordA, const Record &_recordB) {
        return _recordA.time < _recordB.time;
    }
};

#endif
