// application.qml

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

import "qrc:/qml"
import "qrc:/qml/widgets"
import "qrc:/qml/components"

// the ROOT window
ApplicationWindow {
    id: idWindowRoot
    // references
    property var gui: QTimeTrialApplicationGui
    visible: true
    flags: Qt.Tool | Qt.FramelessWindowHint | Qt.WindowTransparentForInput
    color: "transparent"
    x: 0
    y: 0
    width: gui.guiSize.x
    height: gui.guiSize.y
    // the MENU window
    Window {
        id: idWindowMenu
        visible: gui.showWidgetMenu
        flags: Qt.Tool | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
        color: "transparent"
        x: 6 * gui.guiScale
        y: 43 * gui.guiScale
        width: 48 * gui.guiScale
        height: 945 * gui.guiScale
        // the MENU widget
        WidgetMenu {
            id: idWidgetMenu
            anchors.fill: parent
        }
    }
    // the MENU CONTENT window
    Window {
        id: idWindowMenuContent
        visible: gui.showWidgetAbout || gui.showWidgetDrivers || gui.showWidgetRecords || gui.showWidgetOptions
        flags: Qt.Tool | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
        color: "transparent"
        x: 60 * gui.guiScale
        y: 43 * gui.guiScale
        width: 878 * gui.guiScale
        height: 945 * gui.guiScale
        WidgetAbout {
            id: idWidgetAbout
            visible: gui.showWidgetAbout
            anchors.fill: parent
        }
        WidgetDrivers {
            id: idWidgetDrivers
            visible: gui.showWidgetDrivers
            anchors.fill: parent
        }
        WidgetRecords {
            id: idWidgetRecords
            visible: gui.showWidgetRecords
            anchors.fill: parent
        }
        WidgetOptions {
            id: idWidgetOptions
            visible: gui.showWidgetOptions
            anchors.fill: parent
        }
    }
    // the HUD window
    Window {
        id: idWindowHUD
        visible: gui.showHud
        flags: Qt.Tool | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.WindowTransparentForInput
        color: "transparent"
        x: 0
        y: 0
        width: gui.guiSize.x
        height: gui.guiSize.y
        // the HUD widget
        WidgetHud {
            id: idWidgetHud
            anchors.fill: parent
        }
    }
}
