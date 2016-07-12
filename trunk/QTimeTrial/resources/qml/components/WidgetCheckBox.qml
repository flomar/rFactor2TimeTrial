// WidgetCheckBox.qml

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "qrc:/qml"
import "qrc:/qml/widgets"
import "qrc:/qml/components"

Item {
    id: idItemRoot
    // references
    property var gui: QTimeTrialApplicationGui
    // visual properties
    property string text
    // internal properties
    property bool hovered: enabled ? idMouseArea.containsMouse : false
    property bool pressed: enabled ? idMouseArea.containsMouse && idMouseArea.pressed : false
    property bool checked: false
    // signals
    signal signalClicked()
    // text
    Item {
        id: idItemText
        anchors.fill: parent
        anchors.margins: 5.0 * gui.guiScale
        RowLayout {
            anchors.fill: parent
            spacing: 0
            Item {
                id: idItemTextChecked
                Layout.preferredWidth: parent.height
                Layout.preferredHeight: parent.height
                // background and borders
                Item {
                    id: idItemBackgroundAndBorders
                    anchors.fill: parent
                    Rectangle {
                        id: idItemBackground
                        anchors.fill: parent
                        anchors.margins: ApplicationStyle.commonSizeBorder
                        color: ApplicationStyle.widgetCheckBoxColorBackground
                    }
                    // border (left)
                    Rectangle {
                        anchors.fill: parent
                        anchors.rightMargin: parent.width - ApplicationStyle.commonSizeBorder
                        color: idItemRoot.pressed ? ApplicationStyle.widgetCheckBoxColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetCheckBoxColorForegroundHovered : ApplicationStyle.widgetCheckBoxColorForeground
                    }
                    // border (right)
                    Rectangle {
                        anchors.fill: parent
                        anchors.leftMargin: parent.width - ApplicationStyle.commonSizeBorder
                        color: idItemRoot.pressed ? ApplicationStyle.widgetCheckBoxColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetCheckBoxColorForegroundHovered : ApplicationStyle.widgetCheckBoxColorForeground
                    }
                    // border (top)
                    Rectangle {
                        anchors.fill: parent
                        anchors.leftMargin: ApplicationStyle.commonSizeBorder
                        anchors.rightMargin: ApplicationStyle.commonSizeBorder
                        anchors.bottomMargin: parent.height - ApplicationStyle.commonSizeBorder
                        color: idItemRoot.pressed ? ApplicationStyle.widgetCheckBoxColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetCheckBoxColorForegroundHovered : ApplicationStyle.widgetCheckBoxColorForeground
                    }
                    // border (bottom)
                    Rectangle {
                        anchors.fill: parent
                        anchors.leftMargin: ApplicationStyle.commonSizeBorder
                        anchors.rightMargin: ApplicationStyle.commonSizeBorder
                        anchors.topMargin: parent.height - ApplicationStyle.commonSizeBorder
                        color: idItemRoot.pressed ? ApplicationStyle.widgetCheckBoxColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetCheckBoxColorForegroundHovered : ApplicationStyle.widgetCheckBoxColorForeground
                    }
                }
                Text {
                    id: idTextChecked
                    anchors.fill: parent
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text: idItemRoot.checked ? "X" : " "
                    font.family: ApplicationStyle.fontBitwise.name
                    font.pixelSize: parent.height * 0.5
                    color: idItemRoot.pressed ? ApplicationStyle.widgetCheckBoxColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetCheckBoxColorForegroundHovered : ApplicationStyle.widgetCheckBoxColorForeground
                }
            }
            Item {
                id: idItemSpacer
                Layout.preferredWidth: 10.0 * gui.guiScale
                Layout.preferredHeight: parent.height
            }
            Item {
                id: idItemTextDescription
                Layout.preferredWidth: parent.width - parent.height - 10.0 * gui.guiScale
                Layout.preferredHeight: parent.height
                Text {
                    id: idTextDescription
                    anchors.fill: parent
                    horizontalAlignment: Qt.AlignLeft
                    verticalAlignment: Qt.AlignVCenter
                    text: idItemRoot.text
                    font.family: ApplicationStyle.fontBitwise.name
                    font.pixelSize: parent.height * 0.8
                    color: idItemRoot.pressed ? ApplicationStyle.widgetCheckBoxColorForegroundPressed : idItemRoot.hovered ? ApplicationStyle.widgetCheckBoxColorForegroundHovered : ApplicationStyle.widgetCheckBoxColorForeground
                }
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
                checked = !checked
                idItemRoot.signalClicked()
            }
        }
    }
}

