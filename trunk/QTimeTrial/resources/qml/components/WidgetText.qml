// WidgetText.qml

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
    property var gui: QTimeTrialApplicationGui
    // visual properties
    property string text
    property real textAngle: 0.0
    property string linkText
    property real fontPixelSize
    property color fontColor
    property int fontHorizontalAlignment
    property int fontVerticalAlignment
    // text
    Text {
        id: idText
        anchors.fill: parent
        text: idItemRoot.text
        font.family: ApplicationStyle.fontBitwise.name
        font.pixelSize: idItemRoot.fontPixelSize ? idItemRoot.fontPixelSize : 24 * gui.guiScale
        color: idItemRoot.fontColor ? idItemRoot.fontColor : ApplicationStyle.widgetTextColorText
        linkColor: ApplicationStyle.widgetTextColorLink
        onLinkActivated: Qt.openUrlExternally(linkText)
        horizontalAlignment: idItemRoot.fontHorizontalAlignment ? idItemRoot.fontHorizontalAlignment : Qt.AlignLeft
        verticalAlignment: idItemRoot.fontVerticalAlignment ? idItemRoot.fontVerticalAlignment : Qt.AlignTop
        wrapMode: Text.WordWrap
        transform: Rotation {
            origin.x: idText.width / 2
            origin.y: idText.height / 2
            angle: idItemRoot.textAngle
        }
    }
}
