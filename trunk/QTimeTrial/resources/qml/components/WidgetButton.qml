// WidgetButton.qml

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
    property string text
    property real textAngle: 0.0
    // internal properties
    property bool hovered: enabled ? idMouseArea.containsMouse : false
    property bool pressed: enabled ? idMouseArea.containsMouse && idMouseArea.pressed : false
    // signals
    signal signalClicked()
    // background and borders
    Item {
        id: idItemBackgroundAndBorders
        anchors.fill: parent
        Rectangle {
            id: idItemBackground
            anchors.fill: parent
            anchors.margins: ApplicationStyle.commonSizeBorder
            color: ApplicationStyle.widgetButtonColorBackground
        }
        // border (left)
        Rectangle {
            anchors.fill: parent
            anchors.rightMargin: parent.width - ApplicationStyle.commonSizeBorder
            color: !idItemRoot.enabled ? ApplicationStyle.widgetButtonColorForeground : idItemRoot.pressed ? ApplicationStyle.widgetButtonColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetButtonColorForegroundHovered : ApplicationStyle.widgetButtonColorForeground
        }
        // border (right)
        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: parent.width - ApplicationStyle.commonSizeBorder
            color: !idItemRoot.enabled ? ApplicationStyle.widgetButtonColorForeground : idItemRoot.pressed ? ApplicationStyle.widgetButtonColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetButtonColorForegroundHovered : ApplicationStyle.widgetButtonColorForeground
        }
        // border (top)
        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: ApplicationStyle.commonSizeBorder
            anchors.rightMargin: ApplicationStyle.commonSizeBorder
            anchors.bottomMargin: parent.height - ApplicationStyle.commonSizeBorder
            color: !idItemRoot.enabled ? ApplicationStyle.widgetButtonColorForeground : idItemRoot.pressed ? ApplicationStyle.widgetButtonColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetButtonColorForegroundHovered : ApplicationStyle.widgetButtonColorForeground
        }
        // border (bottom)
        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: ApplicationStyle.commonSizeBorder
            anchors.rightMargin: ApplicationStyle.commonSizeBorder
            anchors.topMargin: parent.height - ApplicationStyle.commonSizeBorder
            color: !idItemRoot.enabled ? ApplicationStyle.widgetButtonColorForeground : idItemRoot.pressed ? ApplicationStyle.widgetButtonColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetButtonColorForegroundHovered : ApplicationStyle.widgetButtonColorForeground
        }
    }
    // text
    Item {
        id: idItemText
        anchors.fill: parent
        Text {
            id: idText
            anchors.centerIn: parent
            text: idItemRoot.text
            font.family: ApplicationStyle.fontBitwise.name
            font.pixelSize: idItemRoot.textAngle == 0 ? parent.height * 0.50 : parent.width * 0.50
            color: !idItemRoot.enabled ? ApplicationStyle.widgetButtonColorForeground : idItemRoot.pressed ? ApplicationStyle.widgetButtonColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetButtonColorForegroundHovered : ApplicationStyle.widgetButtonColorForeground
            transform: Rotation {
                origin.x: idText.width / 2
                origin.y: idText.height / 2
                angle: idItemRoot.textAngle
            }
        }
    }
    // mouse area
    MouseArea {
        id: idMouseArea
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton
        onClicked: {
            if(idItemRoot.hovered) {
                idItemRoot.signalClicked()
            }
        }
    }
}

