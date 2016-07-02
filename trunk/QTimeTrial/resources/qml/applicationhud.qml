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
            x: 68 * gui.guiScale
            y: 8 * gui.guiScale
            width: 150 * gui.guiScale
            height: 20 * gui.guiScale
            Text {
                id: idTextItemLap
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
            id: idItemLst
            x: 360 * gui.guiScale
            y: 8 * gui.guiScale
            width: 150 * gui.guiScale
            height: 20 * gui.guiScale
            Text {
                id: idTextItemLst
                anchors.fill: parent
                text: gui.stringLstTime
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 20 * gui.guiScale
            }
        }
        Item {
            id: idItemDriver
            x: 810 * gui.guiScale
            y: 7 * gui.guiScale
            width: 300 * gui.guiScale
            height: 50 * gui.guiScale
            Text {
                id: idTextItemDriver
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
            id: idItemBst
            x: 1410 * gui.guiScale
            y: 8 * gui.guiScale
            width: 150 * gui.guiScale
            height: 20 * gui.guiScale
            Text {
                id: idTextItemBst
                anchors.fill: parent
                text: gui.stringBstTime
                horizontalAlignment: Qt.AlignRight
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 20 * gui.guiScale
            }
        }
        Item {
            id: idItemRec
            x: 1702 * gui.guiScale
            y: 8 * gui.guiScale
            width: 150 * gui.guiScale
            height: 20 * gui.guiScale
            Text {
                id: idTextItemRec
                anchors.fill: parent
                text: gui.stringRecTime
                horizontalAlignment: Qt.AlignRight
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 20 * gui.guiScale
            }
        }
        Item {
            id: idItemRPM
            x: 660 * gui.guiScale
            y: 966 * gui.guiScale
            width: 200 * gui.guiScale
            height: 100 * gui.guiScale
            Text {
                id: idTextItemRPM
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
            y: 966 * gui.guiScale
            width: 100 * gui.guiScale
            height: 100 * gui.guiScale
            Text {
                id: idTextItemGear
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
            x: 1060 * gui.guiScale
            y: 966 * gui.guiScale
            width: 200 * gui.guiScale
            height: 100 * gui.guiScale
            Text {
                id: idTextItemSpeed
                anchors.fill: parent
                text: gui.intSpeed
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: gui.boolSpeedLimiterActive ? Qt.rgba(1.0, 0.0, 0.0, 1.0) : Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 48 * gui.guiScale
            }
        }
        Item {
            id: idItemFuel
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
            id: idItemEngine
            x: 300 * gui.guiScale
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
            id: idItemBrakes
            x: 1600 * gui.guiScale
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
            id: idItemTires
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
            id: idItemRPMLEDs
            x: 662 * gui.guiScale
            y: 934 * gui.guiScale
            width: 596 * gui.guiScale
            height: 16 * gui.guiScale
            Image {
                x: 20 * gui.guiScale * 0
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 0) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 1
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 1) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 2
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 2) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 3
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 3) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 4
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 4) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 5
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 5) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 6
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 6) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 7
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 7) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 8
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 8) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 9
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 9) return "../png/LED_GREEN.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 10
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 10) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 11
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 11) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 12
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 12) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 13
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 13) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 14
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 14) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 15
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 15) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 16
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 16) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 17
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 17) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 18
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 18) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 19
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 19) return "../png/LED_YELLOW.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 20
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 20) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 21
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 21) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 22
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 22) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 23
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 23) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 24
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 24) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 25
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 25) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 26
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 26) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 27
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 27) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 28
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 28) return "../png/LED_RED.png"
                    return "../png/LED_OFF.png"
                }
            }
            Image {
                x: 20 * gui.guiScale * 29
                y: 0
                width: 16 * gui.guiScale
                height: 16 * gui.guiScale
                source: {
                    if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 29) return "../png/LED_RED.png"
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
            Text {
                id: idTextItemLapInformation
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
                id: idTextItemLapInformationAbsoluteBest
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
                id: idTextItemLapInformationPersonalBest
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
                    idTextItemLapInformation.text = infoLapTime
                    idTextItemLapInformationAbsoluteBest.text = infoAbsolute
                    idTextItemLapInformationPersonalBest.text = infoPersonal
                    idTextItemLapInformationAbsoluteBest.color = absoluteBest ? Qt.rgba(0.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 0.0, 0.0, 1.0)
                    idTextItemLapInformationPersonalBest.color = personalBest ? Qt.rgba(0.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 0.0, 0.0, 1.0)
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
