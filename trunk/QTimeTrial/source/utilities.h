// utilities.h

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <main.h>

namespace Utilities {

    namespace Core {

        qint64 getMillisecondsSinceEpoch();

        QString timeInMillisecondsToStringInMinutesSecondsMilliseconds(const qint64 _time);

        QString timeInMillisecondsToStringDate(const qint64 _time);

    }

    namespace Database {

        QVariantMap convertSqlRecordToVariantMap(const QSqlRecord &_record);

        QSqlRecord convertVariantMapToSqlRecord(const QVariantMap &_variantMap, const QStringList &_listFieldNames);

        qint64 createSmallestAvailableIdentifier(QSqlRelationalTableModel *_model);

        QSqlRecord getRecord(QSqlRelationalTableModel *_model, const qint64 _identifier);

        qint64 addRecord(QSqlRelationalTableModel *_model, const QSqlRecord &_record);

        qint64 setRecord(QSqlRelationalTableModel *_model, const QSqlRecord &_record);

        qint64 removeRecord(QSqlRelationalTableModel *_model, const qint64 _identifier);

        bool compareLapsByTime(const QVariantMap &_lapA, const QVariantMap &_lapB);

    }

}

#endif
