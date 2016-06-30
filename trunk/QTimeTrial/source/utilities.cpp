// utilities.cpp

#include <utilities.h>

namespace Utilities {

    namespace Core {

        int64_t getMillisecondsSinceEpoch() {
            return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
        }

        QString timeInMillisecondsToStringInMinutesSecondsMilliseconds(const int64_t _time) {
            int64_t time = _time;
            // convert time into integers for milliseconds, seconds, and minutes
            int64_t intMilliseconds = time % 1000;
            time /= 1000;
            int64_t intSeconds = time % 60;
            time /= 60;
            int64_t intMinutes = time;
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

        QString timeInMillisecondsToStringDate(const int64_t _time) {
            QDateTime dateTime;
            dateTime.setMSecsSinceEpoch(_time);
            return dateTime.toString("yyyy/MM/dd");
        }

    }

    namespace Containers {

    }

    namespace Graphics {

        QRect getRectInset(const QRect &_rect, const int _insetThickness) {
            return QRect(_rect.x() + _insetThickness, _rect.y() + _insetThickness, _rect.width() - _insetThickness * 2, _rect.height() - _insetThickness * 2);
        }

    }

}
