// Widget.qml

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
    // properties
    property real spacing: 20.0
    // container properties
    property alias containerTitle: idItemContainerTitle
    property alias containerContent: idItemContainerContent
    // background and borders
    Item {
        id: idItemBackgroundAndBorders
        anchors.fill: parent
        Rectangle {
            id: idItemBackground
            anchors.fill: parent
            anchors.margins: ApplicationStyle.commonSizeBorder
            color: ApplicationStyle.widgetColorBackground
        }
        // border (left)
        Rectangle {
            anchors.fill: parent
            anchors.rightMargin: parent.width - ApplicationStyle.commonSizeBorder
            color: ApplicationStyle.widgetColorForeground
        }
        // border (right)
        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: parent.width - ApplicationStyle.commonSizeBorder
            color: ApplicationStyle.widgetColorForeground
        }
        // border (top)
        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: ApplicationStyle.commonSizeBorder
            anchors.rightMargin: ApplicationStyle.commonSizeBorder
            anchors.bottomMargin: parent.height - ApplicationStyle.commonSizeBorder
            color: ApplicationStyle.widgetColorForeground
        }
        // border (bottom)
        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: ApplicationStyle.commonSizeBorder
            anchors.rightMargin: ApplicationStyle.commonSizeBorder
            anchors.topMargin: parent.height - ApplicationStyle.commonSizeBorder
            color: ApplicationStyle.widgetColorForeground
        }
    }
    // container title
    Item {
        id: idItemContainerTitle
        anchors.fill: parent
        anchors.leftMargin: parent.spacing * gui.guiScale
        anchors.rightMargin: parent.spacing * gui.guiScale
        anchors.topMargin: parent.spacing * gui.guiScale
        anchors.bottomMargin: parent.height - (parent.spacing + 50.0) * gui.guiScale
    }
    // container content
    Item {
        id: idItemContainerContent
        anchors.fill: parent
        anchors.leftMargin: parent.spacing * gui.guiScale
        anchors.rightMargin: parent.spacing * gui.guiScale
        anchors.topMargin: (parent.spacing + 50.0 + parent.spacing) * gui.guiScale
        anchors.bottomMargin: parent.spacing * gui.guiScale
    }
}
