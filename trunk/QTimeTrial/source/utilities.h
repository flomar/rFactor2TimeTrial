// utilities.h

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <main.h>

namespace Utilities {

    namespace Core {

        int64_t getMillisecondsSinceEpoch();

        QString timeInMillisecondsToStringInMinutesSecondsMilliseconds(const int64_t _time);

        QString timeInMillisecondsToStringDate(const int64_t _time);

    }

    namespace Containers {

        template<class TypeKey, class TypeValue>
        TypeKey getSmallestAvailableIdentifier(const QMap<TypeKey, TypeValue*> &_map) {
            const TypeKey biggestIdentifier = std::numeric_limits<TypeKey>::max();
            for (TypeKey identifier = 1; identifier < biggestIdentifier; identifier++) {
                if (!_map.contains(identifier)) {
                    return identifier;
                }
            }
            return 0;
        }

    }

    namespace Graphics {

        QRect getRectInset(const QRect &_rect, const int _insetThickness);

    }

}

#endif
