// WidgetTextInput.qml

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "qrc:/qml"
import "qrc:/qml/widgets"
import "qrc:/qml/components"

Item {
    id: idItemRoot
    // references
    property var db: QTimeTrialApplicationDatabase
    property var gui: QTimeTrialApplicationGui
    // visual properties
    property alias text: idText.text
    property real fontPixelSize
    property color fontColor
    property int fontHorizontalAlignment
    property int fontVerticalAlignment
    // functions
    function initialize(_text) {
        idText.text = _text
        idText.selectAll()
        idText.forceActiveFocus()
    }
    // background
    Rectangle {
        anchors.fill: parent
        color: ApplicationStyle.widgetTextInputColorBackground
    }
    // text
    Item {
        anchors.fill: parent
        anchors.margins: 10 * gui.guiScale
        TextInput {
            id: idText
            anchors.fill: parent
            text: idItemRoot.text
            font.family: ApplicationStyle.fontBitwise.name
            font.pixelSize: idItemRoot.fontPixelSize ? idItemRoot.fontPixelSize : 24 * gui.guiScale
            color: idItemRoot.fontColor ? idItemRoot.fontColor : ApplicationStyle.widgetTextInputColorText
            horizontalAlignment: idItemRoot.fontHorizontalAlignment ? idItemRoot.fontHorizontalAlignment : Qt.AlignLeft
            verticalAlignment: idItemRoot.fontVerticalAlignment ? idItemRoot.fontVerticalAlignment : Qt.AlignVCenter
            wrapMode: Text.WordWrap
            selectByMouse: true
        }
    }
}
