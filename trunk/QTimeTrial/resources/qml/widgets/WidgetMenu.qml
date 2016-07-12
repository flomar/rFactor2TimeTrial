// WidgetMenu.qml

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
    // buttons
    ColumnLayout {
        anchors.fill: parent
        WidgetButton {
            id: idWidgetButtonAbout
            text: "About"
            textAngle: -90
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height / 8
            onSignalClicked: gui.signalWidgetMenuClickedButtonAbout()
        }
        WidgetButton {
            id: idWidgetButtonDrivers
            text: "Drivers"
            textAngle: -90
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height / 8
            onSignalClicked: gui.signalWidgetMenuClickedButtonDrivers()
        }
        WidgetButton {
            id: idWidgetButtonRecords
            text: "Records"
            textAngle: -90
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height / 8
            onSignalClicked: gui.signalWidgetMenuClickedButtonRecords()
        }
        WidgetButton {
            id: idWidgetButtonOptions
            text: "Options"
            textAngle: -90
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height / 8
            onSignalClicked: gui.signalWidgetMenuClickedButtonOptions()
        }
        Item {
            Layout.fillHeight: true
        }
        WidgetButton {
            id: idWidgetButtonQuit
            text: "Quit"
            textAngle: -90
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height / 8
            onSignalClicked: gui.signalWidgetMenuClickedButtonQuit()
            // in order to not introduce database inconsistencies, the
            // quit button must not be pressed while a session is running
            enabled: QTimeTrialApplicationDatabase.currentSession["Identifier"] ? QTimeTrialApplicationDatabase.currentSession["Identifier"] === 0 : true
        }
    }
}

