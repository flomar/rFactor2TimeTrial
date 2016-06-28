// applicationhud.qml

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "."

Item {
    id: idItemRoot
    anchors.fill: parent
    visible: gui.showHud
    property var gui: QTimeTrialApplicationGui
    // HUD
    Item {
        id: idItemHud
        anchors.fill: parent
        Image {
            id: idImageHud
            anchors.fill: parent
            source: "../png/HUD.png"
        }
        Item {
            id: idItemLap
            x: 75
            y: 6
            width: 200
            height: 20
            Text {
                anchors.fill: parent
                text: gui.stringLapTime
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 20
            }
        }
        Item {
            id: idItemDriver
            x: 760
            y: 7
            width: 400
            height: 50
            Text {
                anchors.fill: parent
                text: gui.stringDriver
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 32
            }
        }
        Item {
            id: idItemRun
            x: 1645
            y: 6
            width: 200
            height: 20
            Text {
                anchors.fill: parent
                text: gui.stringRunTime
                horizontalAlignment: Qt.AlignRight
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 20
            }
        }
        Item {
            id: idItemRPM
            x: 730
            y: 984
            width: 160
            height: 64
            Text {
                anchors.fill: parent
                text: gui.intEngineRPMCurrent
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 40
            }
        }
        Item {
            id: idItemGear
            x: 910
            y: 966
            width: 100
            height: 100
            Text {
                anchors.fill: parent
                text: gui.stringGear
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 50
            }
        }
        Item {
            id: idItemSpeed
            x: 1030
            y: 984
            width: 160
            height: 64
            Text {
                anchors.fill: parent
                text: gui.intSpeed
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 40
            }
        }
        Item {
            id: idItemFuelLED
            x: 8
            y: 1054
            width: 20
            height: 20
            Image {
                anchors.fill: parent
                source: {
                    var fuel = gui.intFuelCurrent / gui.intFuelMaximum
                    var limitRed = 0.10
                    if(fuel < limitRed) return "../png/LED_RED.png"
                    var limitYellow = 0.50
                    if(fuel < limitYellow) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
        }
        Item {
            id: idItemEngineLED
            x: 250
            y: 1054
            width: 20
            height: 20
            Image {
                anchors.fill: parent
                source: {
                    if(gui.boolEngineOverheating) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
        }
        Item {
            id: idItemRPMLimiterLED
            x: 670
            y: 1000
            width: 40
            height: 40
            Image {
                anchors.fill: parent
                source: {
                    if(gui.intEngineRPMPercentage > 90) return "../png/LED_RED.png"
                    if(gui.intEngineRPMPercentage > 70) return "../png/LED_YELLOW.png"
                    if(gui.intEngineRPMPercentage > 50) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
        }
        Item {
            id: idItemSpeedLimiterLED
            x: 1210
            y: 1000
            width: 40
            height: 40
            Image {
                anchors.fill: parent
                source: {
                    if(gui.boolSpeedLimiterActive) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
        }
        Item {
            id: idItemBrakesLED
            x: 1650
            y: 1054
            width: 20
            height: 20
            Image {
                anchors.fill: parent
                source: {
                    var limitRed = 750.0
                    if(gui.intBrakeTemperatureFrontLeft > limitRed) return "../png/LED_RED.png"
                    if(gui.intBrakeTemperatureFrontRight > limitRed) return "../png/LED_RED.png"
                    if(gui.intBrakeTemperatureRearLeft > limitRed) return "../png/LED_RED.png"
                    if(gui.intBrakeTemperatureRearRight > limitRed) return "../png/LED_RED.png"
                    var limitYellow = 500.0
                    if(gui.intBrakeTemperatureFrontLeft > limitYellow) return "../png/LED_YELLOW.png"
                    if(gui.intBrakeTemperatureFrontRight > limitYellow) return "../png/LED_YELLOW.png"
                    if(gui.intBrakeTemperatureRearLeft > limitYellow) return "../png/LED_YELLOW.png"
                    if(gui.intBrakeTemperatureRearRight > limitYellow) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
        }
        Item {
            id: idItemTiresLED
            x: 1892
            y: 1054
            width: 20
            height: 20
            Image {
                anchors.fill: parent
                source: {
                    var limitRed = 10.0
                    if(gui.intTireWearFrontLeft < limitRed) return "../png/LED_RED.png"
                    if(gui.intTireWearFrontRight < limitRed) return "../png/LED_RED.png"
                    if(gui.intTireWearRearLeft < limitRed) return "../png/LED_RED.png"
                    if(gui.intTireWearRearRight < limitRed) return "../png/LED_RED.png"
                    var limitYellow = 50.0
                    if(gui.intTireWearFrontLeft < limitYellow) return "../png/LED_YELLOW.png"
                    if(gui.intTireWearFrontRight < limitYellow) return "../png/LED_YELLOW.png"
                    if(gui.intTireWearRearLeft < limitYellow) return "../png/LED_YELLOW.png"
                    if(gui.intTireWearRearRight < limitYellow) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
        }
    }
}
