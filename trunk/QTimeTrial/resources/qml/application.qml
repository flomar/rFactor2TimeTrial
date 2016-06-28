// application.qml

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "."

ApplicationWindow {
    id: idApplicationWindow
    visible: true
    width: QTimeTrialApplicationGui.guiSize.x
    height: QTimeTrialApplicationGui.guiSize.y
    color: "transparent"
    flags: Qt.Tool | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.WindowTransparentForInput
    title: qsTr("QTimeTrial")
    // the application HUD
    ApplicationHud {
        id: idApplicationHud
        anchors.fill: parent
    }
}
