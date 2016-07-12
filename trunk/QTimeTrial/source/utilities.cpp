// utilities.cpp

#include <utilities.h>

namespace Utilities {

    namespace Core {

        qint64 getMillisecondsSinceEpoch() {
            return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
        }

        QString timeInMillisecondsToStringInMinutesSecondsMilliseconds(const qint64 _time) {
            qint64 time = _time;
            // convert time into integers for milliseconds, seconds, and minutes
            qint64 intMilliseconds = time % 1000;
            time /= 1000;
            qint64 intSeconds = time % 60;
            time /= 60;
            qint64 intMinutes = time;
            // convert time into strings for milliseconds, seconds, and minutes
            QString stringMilliseconds = QString::number(intMilliseconds);
            QString stringSeconds = QString::number(intSeconds);
            QString stringMinutes = QString::number(intMinutes);
            // add padding for milliseconds and seconds
            while(stringMilliseconds.length() < 3) stringMilliseconds.prepend("0");
            while(stringSeconds.length() < 2) stringSeconds.prepend("0");
            // return result string
            return QString("%1:%2:%3").arg(stringMinutes).arg(stringSeconds).arg(stringMilliseconds);
        }

        QString timeInMillisecondsToStringDate(const qint64 _time) {
            QDateTime dateTime;
            dateTime.setMSecsSinceEpoch(_time);
            return dateTime.toString("yyyy-MM-dd");
        }

    }

    namespace Database {

        QVariantMap convertSqlRecordToVariantMap(const QSqlRecord &_record) {
            QVariantMap variantMap;
            for(int indexField=0; indexField<_record.count(); indexField++) {
                variantMap.insert(_record.fieldName(indexField), _record.value(indexField));
            }
            return variantMap;
        }

        QSqlRecord convertVariantMapToSqlRecord(const QVariantMap &_variantMap, const QStringList &_listFieldNames) {
            QSqlRecord record;
            foreach(const QString fieldName, _variantMap.keys()) {
                if(_listFieldNames.contains(fieldName)) {
                    record.append(QSqlField(fieldName));
                    record.setValue(fieldName, _variantMap.value(fieldName));
                }
            }
            return record;
        }

        qint64 createSmallestAvailableIdentifier(QSqlRelationalTableModel *_model) {
            if(_model) {
                _model->setFilter(QString::null);
                _model->select();
                QSet<qint64> identifiersOccupied;
                for(int indexRow=0; indexRow<_model->rowCount(); indexRow++) {
                    identifiersOccupied.insert(_model->record(indexRow).value("Identifier").toLongLong());
                }
                for(qint64 identifier=1; identifier<std::numeric_limits<qint64>::max(); identifier++) {
                    if(!identifiersOccupied.contains(identifier)) {
                        return identifier;
                    }
                }
            }
            return 0;
        }

        QSqlRecord getRecord(QSqlRelationalTableModel *_model, const qint64 _identifier) {
            QSqlRecord record;
            if(_model) {
                _model->setFilter(QString::null);
                _model->select();
                for(int indexRow=0; indexRow<_model->rowCount(); indexRow++) {
                    if(_model->record(indexRow).value("Identifier").toLongLong() == _identifier) {
                        record = _model->record(indexRow);
                        return record;
                    }
                }
            }
            return record;
        }

        qint64 addRecord(QSqlRelationalTableModel *_model, const QSqlRecord &_record) {
            if(_model) {
                _model->setFilter(QString::null);
                _model->select();
                if(_model->insertRecord(-1, _record)) {
                    return _record.value("Identifier").toLongLong();
                }
            }
            return 0;
        }

        qint64 setRecord(QSqlRelationalTableModel *_model, const QSqlRecord &_record) {
            if(_model) {
                _model->setFilter(QString::null);
                _model->select();
                for(int indexRow=0; indexRow<_model->rowCount(); indexRow++) {
                    if(_model->record(indexRow).value("Identifier").toLongLong() == _record.value("Identifier").toLongLong()) {
                        if(_model->setRecord(indexRow, _record)) {
                            return _record.value("Identifier").toLongLong();
                        }
                    }
                }
            }
            return 0;
        }

        qint64 removeRecord(QSqlRelationalTableModel *_model, const qint64 _identifier) {
            if(_model) {
                _model->setFilter(QString::null);
                _model->select();
                if(_identifier > 0) {
                    for(int indexRow=0; indexRow<_model->rowCount(); indexRow++) {
                        if(_model->record(indexRow).value("Identifier").toLongLong() == _identifier) {
                            if(_model->removeRow(indexRow)) {
                                return _identifier;
                            }
                        }
                    }
                }
            }
            return 0;
        }

        bool compareLapsByTime(const QVariantMap &_lapA, const QVariantMap &_lapB) {
            return _lapA.value("Time").toLongLong() < _lapB.value("Time").toLongLong();
        }

    }

}
