// WidgetAbout.qml

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
    visible: gui.showWidgetAbout
    // visuals
    Widget {
        id: idWidget
        anchors.fill: parent
        WidgetTitle {
            anchors.fill: idWidget.containerTitle
            text: "/ About"
        }
        WidgetText {
            anchors.fill: idWidget.containerContent
            text: "<b>QTimeTrial (C) 2016 flomar</b><br><br>The QTimeTrial application is part of the rFactor2TimeTrial project.<br><br>Please refer to the project documentation for detailed information:<br><br><a href=\"https://github.com/flomar/rFactor2TimeTrial\">https://github.com/flomar/rFactor2TimeTrial</a>"
            linkText: "https://github.com/flomar/rFactor2TimeTrial"
            fontPixelSize: 24 * gui.guiScale
            fontColor: Qt.rgba(1.0, 1.0, 1.0, 1.0)
        }
    }
}
