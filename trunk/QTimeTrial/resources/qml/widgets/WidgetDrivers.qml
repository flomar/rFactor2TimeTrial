// WidgetDrivers.qml

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
    // properties
    visible: gui.showWidgetDrivers
    // initialization
    onVisibleChanged: {
        idWidgetCreateDriver.visible = false
    }
    // visuals
    Widget {
        id: idWidget
        anchors.fill: parent
        visible: !idWidgetCreateDriver.visible
        WidgetTitle {
            anchors.fill: idWidget.containerTitle
            text: "/ Drivers"
        }
        RowLayout {
            id: idRowLayoutButtons
            anchors.fill: idWidget.containerTitle
            spacing: 10.0 * gui.guiScale
            Item {
                Layout.fillWidth: true
            }
            WidgetButton {
                id: idWidgetButtonCreate
                Layout.preferredWidth: parent.width * 0.125
                Layout.preferredHeight: parent.height
                text: "Create"
                onSignalClicked: {
                    idWidgetCreateDriver.visible = true
                }
            }
            WidgetButton {
                id: idWidgetButtonDelete
                Layout.preferredWidth: parent.width * 0.125
                Layout.preferredHeight: parent.height
                text: "Delete"
                onSignalClicked: {
                    QTimeTrialApplicationDatabase.signalDeleteDriver(idListViewDrivers.identifierSelectedDriver)
                    QTimeTrialApplicationDatabase.signalUpdateDrivers()
                    idListViewDrivers.currentIndex = -1
                }
                enabled: idListViewDrivers.currentIndex != -1
            }
        }
        ColumnLayout {
            id: idColumnLayoutDrivers
            anchors.fill: idWidget.containerContent
            spacing: 10.0 * gui.guiScale
            ListView {
                id: idListViewDrivers
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height
                currentIndex: -1
                spacing: 10.0 * gui.guiScale
                clip: true
                property int identifierSelectedDriver: 0
                model: QTimeTrialApplicationDatabaseModelDrivers
                delegate: Rectangle {
                    width: idListViewDrivers.width
                    height: idListViewDrivers.height / 10
                    color: QTimeTrialApplicationDatabase.currentDriver["Identifier"] === model.Identifier ? Qt.rgba(1.0, 1.0, 0.0, 0.1) : Qt.rgba(1.0, 1.0, 1.0, 0.1)
                    Item {
                        id: idItemDriver
                        anchors.fill: parent
                        anchors.margins: 5.0 * gui.guiScale
                        WidgetText {
                            anchors.fill: parent
                            text: model.Name ? model.Name : ""
                            fontPixelSize: parent.height * 0.9
                            fontColor: QTimeTrialApplicationDatabase.currentDriver["Identifier"] === model.Identifier ? Qt.rgba(1.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 1.0, 1.0, 1.0)
                            fontHorizontalAlignment: Qt.AlignLeft
                            fontVerticalAlignment: Qt.AlignVCenter
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            idListViewDrivers.currentIndex = model.index
                            idListViewDrivers.identifierSelectedDriver = model.Identifier
                            QTimeTrialApplicationDatabase.signalSelectCurrentDriver(model.Identifier)
                        }
                    }
                }
            }
        }
    }
    Widget {
        id: idWidgetCreateDriver
        anchors.fill: parent
        visible: false
        // initialization
        onVisibleChanged: {
            idWidgetTextInputCreateDriver.initialize("NEW DRIVER")
        }
        WidgetTitle {
            anchors.fill: idWidgetCreateDriver.containerTitle
            text: "/ Drivers / Create Driver"
        }
        RowLayout {
            id: idRowLayoutButtonsCreateDriver
            anchors.fill: idWidgetCreateDriver.containerTitle
            spacing: 10.0 * gui.guiScale
            Item {
                Layout.fillWidth: true
            }
            WidgetButton {
                id: idWidgetButtonCreateDriverOK
                Layout.preferredWidth: parent.width * 0.125
                Layout.preferredHeight: parent.height
                text: "OK"
                onSignalClicked: {
                    QTimeTrialApplicationDatabase.signalCreateDriver(idWidgetTextInputCreateDriver.text)
                    QTimeTrialApplicationDatabase.signalUpdateDrivers()
                    idWidgetCreateDriver.visible = false
                }
            }
            WidgetButton {
                id: idWidgetButtonCreateDriverCancel
                Layout.preferredWidth: parent.width * 0.125
                Layout.preferredHeight: parent.height
                text: "Cancel"
                onSignalClicked: {
                    idWidgetCreateDriver.visible = false
                }
            }
        }
        ColumnLayout {
            id: idColumnLayoutCreateDriver
            anchors.fill: idWidgetCreateDriver.containerContent
            spacing: 10.0 * gui.guiScale
            WidgetTextInput {
                id: idWidgetTextInputCreateDriver
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height * 0.1
                text: ""
                fontColor: ApplicationStyle.widgetTextColorText
            }
            Item {
                Layout.fillHeight: true
            }
        }
    }
}
