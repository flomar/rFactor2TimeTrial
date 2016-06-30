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
            x: 75 * gui.guiScale
            y: 6 * gui.guiScale
            width: 200 * gui.guiScale
            height: 20 * gui.guiScale
            Text {
                anchors.fill: parent
                text: gui.stringLapTime
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 20 * gui.guiScale
            }
        }
        Item {
            id: idItemDriver
            x: 760 * gui.guiScale
            y: 7 * gui.guiScale
            width: 400 * gui.guiScale
            height: 50 * gui.guiScale
            Text {
                anchors.fill: parent
                text: gui.stringDriver
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 32 * gui.guiScale
            }
        }
        Item {
            id: idItemRun
            x: 1645 * gui.guiScale
            y: 6 * gui.guiScale
            width: 200 * gui.guiScale
            height: 20 * gui.guiScale
            Text {
                anchors.fill: parent
                text: gui.stringRunTime
                horizontalAlignment: Qt.AlignRight
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 20 * gui.guiScale
            }
        }
        Item {
            id: idItemRPM
            x: 730 * gui.guiScale
            y: 956 * gui.guiScale
            width: 160 * gui.guiScale
            height: 92 * gui.guiScale
            Text {
                anchors.fill: parent
                text: gui.intEngineRPMCurrent
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 48 * gui.guiScale
            }
        }
        Item {
            id: idItemGear
            x: 910 * gui.guiScale
            y: 956 * gui.guiScale
            width: 92 * gui.guiScale
            height: 92 * gui.guiScale
            Text {
                anchors.fill: parent
                text: gui.stringGear
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 60 * gui.guiScale
            }
        }
        Item {
            id: idItemSpeed
            x: 1030 * gui.guiScale
            y: 956 * gui.guiScale
            width: 160 * gui.guiScale
            height: 92 * gui.guiScale
            Text {
                anchors.fill: parent
                text: gui.intSpeed
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 48 * gui.guiScale
            }
        }
        Item {
            id: idItemFuelLED
            x: 8 * gui.guiScale
            y: 1054 * gui.guiScale
            width: 20 * gui.guiScale
            height: 20 * gui.guiScale
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
            x: 250 * gui.guiScale
            y: 1054 * gui.guiScale
            width: 20 * gui.guiScale
            height: 20 * gui.guiScale
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
            x: 622 * gui.guiScale
            y: 956 * gui.guiScale
            width: 92 * gui.guiScale
            height: 92 * gui.guiScale
            Image {
                anchors.fill: parent
                source: {
                    if(gui.intEngineRPMPercentage > 90) return "../png/LED_RPM_LIMITER_RED.png"
                    if(gui.intEngineRPMPercentage > 70) return "../png/LED_RPM_LIMITER_YELLOW.png"
                    if(gui.intEngineRPMPercentage > 50) return "../png/LED_RPM_LIMITER_GREEN.png"
                    return "../png/LED_RPM_LIMITER_OFF.png"
                }
            }
        }
        Item {
            id: idItemSpeedLimiterLED
            x: 1206 * gui.guiScale
            y: 956 * gui.guiScale
            width: 92 * gui.guiScale
            height: 92 * gui.guiScale
            Image {
                anchors.fill: parent
                source: {
                    if(gui.boolSpeedLimiterActive) return "../png/LED_SPEED_LIMITER_RED.png"
                    return "../png/LED_SPEED_LIMITER_OFF.png"
                }
            }
        }
        Item {
            id: idItemBrakesLED
            x: 1650 * gui.guiScale
            y: 1054 * gui.guiScale
            width: 20 * gui.guiScale
            height: 20 * gui.guiScale
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
            x: 1892 * gui.guiScale
            y: 1054 * gui.guiScale
            width: 20 * gui.guiScale
            height: 20 * gui.guiScale
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
        Item {
            id: idItemLapInformation
            anchors.centerIn: parent
            width: 256 * gui.guiScale
            height: 128 * gui.guiScale
            opacity: 0.0
            property real durationVisible: 3000
            Text {
                id: idItemLapInformationText
                anchors.fill: parent
                anchors.bottomMargin: parent.height * 3 / 5
                text: "00:00:000"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 40 * gui.guiScale
                style: Text.Raised
                styleColor: Qt.rgba(0.0, 0.0, 0.0, 1.0)
            }
            Text {
                id: idItemLapInformationTextAbsoluteBest
                anchors.fill: parent
                anchors.topMargin: parent.height * 2 / 5
                anchors.bottomMargin: parent.height * 1 / 5
                text: "00:00:000"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 28 * gui.guiScale
                style: Text.Raised
                styleColor: Qt.rgba(0.0, 0.0, 0.0, 1.0)
            }
            Text {
                id: idItemLapInformationTextPersonalBest
                anchors.fill: parent
                anchors.topMargin: parent.height * 4 / 5
                text: "00:00:000"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 28 * gui.guiScale
                style: Text.Raised
                styleColor: Qt.rgba(0.0, 0.0, 0.0, 1.0)
            }
            Connections {
                target: QTimeTrialApplicationDatabase
                onSignalLapInformation: {
                    // acquire signal parameters
                    var infoLapTime = _infoLapTime
                    var infoAbsolute = _infoAbsolute
                    var infoPersonal = _infoPersonal
                    var absoluteBest = _absoluteBest
                    var personalBest = _personalBest
                    // process signal parameters
                    idItemLapInformationText.text = infoLapTime
                    idItemLapInformationTextAbsoluteBest.text = infoAbsolute
                    idItemLapInformationTextPersonalBest.text = infoPersonal
                    idItemLapInformationTextAbsoluteBest.color = absoluteBest ? Qt.rgba(0.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 0.0, 0.0, 1.0)
                    idItemLapInformationTextPersonalBest.color = personalBest ? Qt.rgba(0.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 0.0, 0.0, 1.0)
                    idSequentialAnimation.start()
                }
            }
            SequentialAnimation {
                id: idSequentialAnimation
                alwaysRunToEnd: true
                PropertyAnimation {
                    target: idItemLapInformation
                    properties: "opacity"
                    from: 0.0
                    to: 1.0
                    duration: 125
                }
                PropertyAnimation {
                    target: idItemLapInformation
                    properties: "opacity"
                    from: 1.0
                    to: 0.0
                    duration: 7375
                }
            }
        }
    }
}
