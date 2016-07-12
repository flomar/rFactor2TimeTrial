// WidgetRecords.qml

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
    visible: gui.showWidgetRecords
    // initialization
    onVisibleChanged: {
        idListViewRecords.currentIndex = -1
        idWidgetCheckBoxRecordsDriver.checked = false
        idWidgetCheckBoxRecordsTrack.checked = true
        idWidgetCheckBoxRecordsCar.checked = false
        QTimeTrialApplicationDatabase.signalUpdateRecords(idWidgetCheckBoxRecordsDriver.checked, idWidgetCheckBoxRecordsTrack.checked, idWidgetCheckBoxRecordsCar.checked)
    }
    // visuals
    Widget {
        id: idWidget
        anchors.fill: parent
        WidgetTitle {
            anchors.fill: idWidget.containerTitle
            text: "/ Records"
        }
        RowLayout {
            id: idRowLayoutButtons
            anchors.fill: idWidget.containerTitle
            spacing: 10.0 * gui.guiScale
            Item {
                Layout.fillWidth: true
            }
            WidgetButton {
                id: idWidgetButtonDelete
                Layout.preferredWidth: parent.width * 0.125
                Layout.preferredHeight: parent.height
                text: "Delete"
                onSignalClicked: {
                    QTimeTrialApplicationDatabase.signalDeleteRecord(idListViewRecords.identifierSelectedRecord)
                    QTimeTrialApplicationDatabase.signalUpdateRecords(idWidgetCheckBoxRecordsDriver.checked, idWidgetCheckBoxRecordsTrack.checked, idWidgetCheckBoxRecordsCar.checked)
                    idListViewRecords.currentIndex = -1
                }
                enabled: idListViewRecords.currentIndex != -1
            }
        }
        ColumnLayout {
            id: idColumnLayoutRecords
            anchors.fill: idWidget.containerContent
            spacing: 10.0 * gui.guiScale
            Item {
                id: idItemListViewRecords
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height * 0.8
                ListView {
                    id: idListViewRecords
                    anchors.fill: parent
                    currentIndex: -1
                    spacing: 10.0 * gui.guiScale
                    clip: true
                    property int identifierSelectedRecord: 0
                    model: QTimeTrialApplicationDatabaseModelRecords
                    delegate: Rectangle {
                        width: idListViewRecords.width
                        height: 100.0 * gui.guiScale
                        color: idListViewRecords.currentIndex === model.index ? Qt.rgba(1.0, 1.0, 0.0, 0.1) : Qt.rgba(1.0, 1.0, 1.0, 0.1)
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 5.0 * gui.guiScale
                            spacing: 0
                            Item {
                                id: idItemTop
                                Layout.preferredWidth: parent.width
                                Layout.preferredHeight: parent.height * 0.4
                                RowLayout {
                                    anchors.fill: parent
                                    anchors.margins: 5.0 * gui.guiScale
                                    spacing: 0
                                    Item {
                                        id: idItemRecordRank
                                        Layout.preferredWidth: parent.width * 0.15
                                        Layout.preferredHeight: parent.height
                                        WidgetText {
                                            anchors.fill: parent
                                            text: "#" + (index + 1)
                                            fontPixelSize: parent.height * 0.9
                                            fontColor: idListViewRecords.currentIndex === model.index ? Qt.rgba(1.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 1.0, 1.0, 1.0)
                                            fontHorizontalAlignment: Qt.AlignLeft
                                            fontVerticalAlignment: Qt.AlignVCenter
                                        }
                                    }
                                    Item {
                                        id: idItemRecordTimeHumanReadable
                                        Layout.preferredWidth: parent.width * 0.20
                                        Layout.preferredHeight: parent.height
                                        WidgetText {
                                            anchors.fill: parent
                                            text: model.TimeHumanReadable ? model.TimeHumanReadable : ""
                                            fontPixelSize: parent.height * 0.9
                                            fontColor: idListViewRecords.currentIndex === model.index ? Qt.rgba(1.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 1.0, 1.0, 1.0)
                                            fontHorizontalAlignment: Qt.AlignLeft
                                            fontVerticalAlignment: Qt.AlignVCenter
                                        }
                                    }
                                    Item {
                                        id: idItemRecordNameDriver
                                        Layout.preferredWidth: parent.width * 0.45
                                        Layout.preferredHeight: parent.height
                                        WidgetText {
                                            anchors.fill: parent
                                            text: model.NameDriver ? model.NameDriver : ""
                                            fontPixelSize: parent.height * 0.9
                                            fontColor: idListViewRecords.currentIndex === model.index ? Qt.rgba(1.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 1.0, 1.0, 1.0)
                                            fontHorizontalAlignment: Qt.AlignLeft
                                            fontVerticalAlignment: Qt.AlignVCenter
                                        }
                                    }
                                    Item {
                                        id: idItemRecordDateHumanReadable
                                        Layout.preferredWidth: parent.width * 0.20
                                        Layout.preferredHeight: parent.height
                                        WidgetText {
                                            anchors.fill: parent
                                            text: model.DateHumanReadable ? model.DateHumanReadable : ""
                                            fontPixelSize: parent.height * 0.9
                                            fontColor: idListViewRecords.currentIndex === model.index ? Qt.rgba(1.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 1.0, 1.0, 1.0)
                                            fontHorizontalAlignment: Qt.AlignRight
                                            fontVerticalAlignment: Qt.AlignVCenter
                                        }
                                    }
                                }
                            }
                            Item {
                                id: idItemBottom
                                Layout.preferredWidth: parent.width
                                Layout.preferredHeight: parent.height * 0.6
                                ColumnLayout {
                                    anchors.fill: parent
                                    anchors.margins: 3.0 * gui.guiScale
                                    anchors.leftMargin: parent.width * 0.35
                                    spacing: 0
                                    Item {
                                        id: idItemRecordNameTrack
                                        Layout.preferredWidth: parent.width
                                        Layout.preferredHeight: parent.height / 3
                                        WidgetText {
                                            anchors.fill: parent
                                            text: model.NameTrack ? model.NameTrack : ""
                                            fontPixelSize: parent.height * 0.85
                                            fontColor: idListViewRecords.currentIndex === model.index ? Qt.rgba(1.0, 1.0, 0.0, 0.5) : Qt.rgba(1.0, 1.0, 1.0, 0.5)
                                            fontHorizontalAlignment: Qt.AlignLeft
                                            fontVerticalAlignment: Qt.AlignVCenter
                                        }
                                    }

                                    Item {
                                        id: idItemRecordNameCar
                                        Layout.preferredWidth: parent.width
                                        Layout.preferredHeight: parent.height / 3
                                        WidgetText {
                                            anchors.fill: parent
                                            text: model.NameCar ? model.NameCar : ""
                                            fontPixelSize: parent.height * 0.85
                                            fontColor: idListViewRecords.currentIndex === model.index ? Qt.rgba(1.0, 1.0, 0.0, 0.5) : Qt.rgba(1.0, 1.0, 1.0, 0.5)
                                            fontHorizontalAlignment: Qt.AlignLeft
                                            fontVerticalAlignment: Qt.AlignVCenter
                                        }
                                    }
                                    Item {
                                        id: idItemRecordTireCompounds
                                        Layout.preferredWidth: parent.width
                                        Layout.preferredHeight: parent.height / 3
                                        WidgetText {
                                            anchors.fill: parent
                                            text: model.NameFrontTireCompound && model.NameRearTireCompound ? model.NameFrontTireCompound + " / " + model.NameRearTireCompound : ""
                                            fontPixelSize: parent.height * 0.85
                                            fontColor: idListViewRecords.currentIndex === model.index ? Qt.rgba(1.0, 1.0, 0.0, 0.5) : Qt.rgba(1.0, 1.0, 1.0, 0.5)
                                            fontHorizontalAlignment: Qt.AlignLeft
                                            fontVerticalAlignment: Qt.AlignVCenter
                                        }
                                    }
                                }
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if(idListViewRecords.currentIndex === model.index) {
                                    idListViewRecords.currentIndex = -1
                                    idListViewRecords.identifierSelectedRecord = 0
                                }
                                else {
                                    idListViewRecords.currentIndex = model.index
                                    idListViewRecords.identifierSelectedRecord = model.Identifier
                                }
                            }
                        }
                    }
                }
            }
            Item {
                id: idItemCheckBoxRecords
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height * 0.2
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 5.0 * gui.guiScale
                    spacing: 0
                    WidgetCheckBox {
                        id: idWidgetCheckBoxRecordsDriver
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: parent.height / 3
                        text: "Show current driver only"
                        onSignalClicked: QTimeTrialApplicationDatabase.signalUpdateRecords(idWidgetCheckBoxRecordsDriver.checked, idWidgetCheckBoxRecordsTrack.checked, idWidgetCheckBoxRecordsCar.checked)
                    }
                    WidgetCheckBox {
                        id: idWidgetCheckBoxRecordsTrack
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: parent.height / 3
                        text: "Show current track only"
                        onSignalClicked: QTimeTrialApplicationDatabase.signalUpdateRecords(idWidgetCheckBoxRecordsDriver.checked, idWidgetCheckBoxRecordsTrack.checked, idWidgetCheckBoxRecordsCar.checked)
                    }
                    WidgetCheckBox {
                        id: idWidgetCheckBoxRecordsCar
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: parent.height / 3
                        text: "Show current car only"
                        onSignalClicked: QTimeTrialApplicationDatabase.signalUpdateRecords(idWidgetCheckBoxRecordsDriver.checked, idWidgetCheckBoxRecordsTrack.checked, idWidgetCheckBoxRecordsCar.checked)
                    }
                }
            }
        }
    }
}
