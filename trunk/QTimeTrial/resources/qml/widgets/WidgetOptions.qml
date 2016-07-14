// WidgetOptions.qml

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
    visible: gui.showWidgetOptions
    // visuals
    Widget {
        id: idWidget
        anchors.fill: parent
        WidgetTitle {
            anchors.fill: idWidget.containerTitle
            text: "/ Options"
        }
        ColumnLayout {
            id: idColumnLayoutOptions
            anchors.fill: idWidget.containerContent
            spacing: 5.0 * gui.guiScale
            // TODO/FIXME
        }
    }
}
