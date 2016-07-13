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
        ColumnLayout {
            id: idColumnLayoutAbout
            anchors.fill: idWidget.containerContent
            spacing: 10.0 * gui.guiScale
            Item {
                id: idItemWidgetTextApplicationName
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height * 0.05
                WidgetText {
                    text: "QTimeTrial"
                    fontPixelSize: 32 * gui.guiScale
                    fontColor: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                    fontHorizontalAlignment: Qt.AlignHCenter
                    fontVerticalAlignment: Qt.AlignVCenter
                }
            }
            Item {
                id: idItemWidgetTextApplicationCopyright
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height * 0.05
                WidgetText {
                    text: "(C) 2016 flomar"
                    fontPixelSize: 16 * gui.guiScale
                    fontColor: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                    fontHorizontalAlignment: Qt.AlignHCenter
                    fontVerticalAlignment: Qt.AlignVCenter
                }
            }
            Item {
                id: idItemImageApplicationLogo
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height * 0.25
                Image {
                    anchors.centerIn: parent
                    width: parent.height
                    height: parent.height
                    source: "/png/logo.png"
                }
            }
            Item {
                id: idItemWidgetTextProjectInformation
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height * 0.25
                WidgetText {
                    text: "The QTimeTrial application is part of the rFactor2TimeTrial project.<br><br>Please refer to the project documentation for detailed information:<br><br><a href=\"https://github.com/flomar/rFactor2TimeTrial\">https://github.com/flomar/rFactor2TimeTrial</a>"
                    linkText: "https://github.com/flomar/rFactor2TimeTrial"
                    fontPixelSize: 24 * gui.guiScale
                    fontColor: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                    fontHorizontalAlignment: Qt.AlignHCenter
                    fontVerticalAlignment: Qt.AlignVCenter
                }
            }
            Item {
                Layout.fillHeight: true
            }
        }
    }
}
