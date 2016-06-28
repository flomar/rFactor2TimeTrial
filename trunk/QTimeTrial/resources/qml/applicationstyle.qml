// applicationstyle.qml

pragma Singleton

import QtQuick 2.7

Item {

    readonly property var fontBitwise: fontBitwise

    FontLoader { id: fontBitwise; source: "qrc:/fonts/FONT_BITWISE" }

}
