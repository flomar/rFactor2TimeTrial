// applicationstyle.qml

pragma Singleton

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {

    // references
    readonly property var db: QTimeTrialApplicationDatabase
    readonly property var gui: QTimeTrialApplicationGui

    // load some fonts
    FontLoader {
        id: idFontBitwise
        source: "qrc:/ttf/Bitwise.ttf"
    }
    FontLoader {
        id: idFontCopperplate
        source: "qrc:/ttf/Copperplate.ttf"
    }
    FontLoader {
        id: idFontTypewriter
        source: "qrc:/ttf/Typewriter.ttf"
    }

    // make fonts available to QML components
    readonly property var fontBitwise: idFontBitwise
    readonly property var fontCopperplate: idFontCopperplate
    readonly property var fontTypewriter: idFontTypewriter

    // common
    readonly property real commonSizeBorder: 3.0 * gui.guiScale

    // Hud
    readonly property color hudColorBackground: Qt.rgba(0.0, 0.0, 0.0, 0.5)
    readonly property color hudColorForeground: Qt.rgba(0.0, 0.0, 0.0, 1.0)
    readonly property color hudColorTextStatic: Qt.rgba(0.8, 0.8, 0.8, 1.0)
    readonly property color hudColorTextDynamic: Qt.rgba(1.0, 1.0, 1.0, 1.0)

    // Widget
    readonly property color widgetColorBackground: Qt.rgba(0.0, 0.0, 0.0, 0.85)
    readonly property color widgetColorForeground: Qt.rgba(1.0, 1.0, 1.0, 1.0)

    // WidgetTitle
    readonly property color widgetTitleColorText: Qt.rgba(1.0, 1.0, 1.0, 1.0)

    // WidgetText
    readonly property color widgetTextColorText: Qt.rgba(1.0, 1.0, 1.0, 1.0)
    readonly property color widgetTextColorLink: Qt.rgba(1.0, 1.0, 0.0, 1.0)

    // WidgetTextInput
    readonly property color widgetTextInputColorBackground: Qt.rgba(1.0, 1.0, 1.0, 0.1)
    readonly property color widgetTextInputColorText: Qt.rgba(1.0, 1.0, 1.0, 1.0)

    // WidgetButton
    readonly property color widgetButtonColorBackground: Qt.rgba(0.0, 0.0, 0.0, 1.0)
    readonly property color widgetButtonColorBackgroundHovered: Qt.rgba(0.0, 0.0, 0.0, 1.0)
    readonly property color widgetButtonColorBackgroundPressed: Qt.rgba(0.0, 0.0, 0.0, 1.0)
    readonly property color widgetButtonColorForeground: Qt.rgba(0.5, 0.5, 0.5, 1.0)
    readonly property color widgetButtonColorForegroundHovered: Qt.rgba(1.0, 1.0, 1.0, 1.0)
    readonly property color widgetButtonColorForegroundPressed: Qt.rgba(1.0, 1.0, 0.0, 1.0)

    // WidgetCheckBox
    readonly property color widgetCheckBoxColorBackground: Qt.rgba(0.0, 0.0, 0.0, 1.0)
    readonly property color widgetCheckBoxColorBackgroundHovered: Qt.rgba(0.0, 0.0, 0.0, 1.0)
    readonly property color widgetCheckBoxColorBackgroundPressed: Qt.rgba(0.0, 0.0, 0.0, 1.0)
    readonly property color widgetCheckBoxColorForeground: Qt.rgba(0.5, 0.5, 0.5, 1.0)
    readonly property color widgetCheckBoxColorForegroundHovered: Qt.rgba(1.0, 1.0, 1.0, 1.0)
    readonly property color widgetCheckBoxColorForegroundPressed: Qt.rgba(1.0, 1.0, 0.0, 1.0)
}
