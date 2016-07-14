// WidgetTitle.qml

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "qrc:/qml"
import "qrc:/qml/widgets"
import "qrc:/qml/components"

Item {
    id: idItemRoot
    anchors.fill: parent
    // references
    property var db: QTimeTrialApplicationDatabase
    property var gui: QTimeTrialApplicationGui
    // visual properties
    property string text
    // title text
    Text {
        id: idText
        anchors.left: parent.left
        anchors.top: parent.top
        text: idItemRoot.text
        font.family: ApplicationStyle.fontBitwise.name
        font.pixelSize: 40 * gui.guiScale
        color: ApplicationStyle.widgetTitleColorText
    }
}
