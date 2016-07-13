// WidgetHud.qml

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
    // hud
    Item {
        id: idItemHud
        anchors.fill: parent
        Image {
            id: idImageHud
            anchors.fill: parent
            source: "/png/hud.png"
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
            id: idItemLapTimeLast
            x: 360 * gui.guiScale
            y: 8 * gui.guiScale
            width: 150 * gui.guiScale
            height: 20 * gui.guiScale
            Text {
                id: idTextItemLapTimeLast
                anchors.fill: parent
                text: gui.stringLapTimeLast
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
            y: 16 * gui.guiScale
            width: 300 * gui.guiScale
            height: 40 * gui.guiScale
            Text {
                id: idTextItemDriver
                anchors.fill: parent
                text: gui.stringDriver
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 40 * gui.guiScale
            }
        }
        Item {
            id: idItemLapTimePersonalBest
            x: 1410 * gui.guiScale
            y: 8 * gui.guiScale
            width: 150 * gui.guiScale
            height: 20 * gui.guiScale
            Text {
                id: idTextItemLapTimePersonalBest
                anchors.fill: parent
                text: gui.stringLapTimePersonalBest
                horizontalAlignment: Qt.AlignRight
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 20 * gui.guiScale
            }
        }
        Item {
            id: idItemLapTimeAbsoluteBest
            x: 1702 * gui.guiScale
            y: 8 * gui.guiScale
            width: 150 * gui.guiScale
            height: 20 * gui.guiScale
            Text {
                id: idTextItemLapTimeAbsoluteBest
                anchors.fill: parent
                text: gui.stringLapTimeAbsoluteBest
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
                    if(fuel < limitRed) return "/png/led_red.png"
                    var limitYellow = 0.50
                    if(fuel < limitYellow) return "/png/led_yellow.png"
                    return "/png/led_off.png"
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
                    if(gui.boolEngineOverheating) return "/png/led_red.png"
                    return "/png/led_off.png"
                }
            }
        }
        Item {
            id: idItemCar
            x: 810 * gui.guiScale
            y: 1056 * gui.guiScale
            width: 300 * gui.guiScale
            height: 20 * gui.guiScale
            Text {
                id: idTextItemCar
                anchors.fill: parent
                text: gui.stringCar
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 0.5)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 16 * gui.guiScale
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
                    if(gui.intBrakeTemperatureFrontLeft > limitRed) return "/png/led_red.png"
                    if(gui.intBrakeTemperatureFrontRight > limitRed) return "/png/led_red.png"
                    if(gui.intBrakeTemperatureRearLeft > limitRed) return "/png/led_red.png"
                    if(gui.intBrakeTemperatureRearRight > limitRed) return "/png/led_red.png"
                    var limitYellow = 500.0
                    if(gui.intBrakeTemperatureFrontLeft > limitYellow) return "/png/led_yellow.png"
                    if(gui.intBrakeTemperatureFrontRight > limitYellow) return "/png/led_yellow.png"
                    if(gui.intBrakeTemperatureRearLeft > limitYellow) return "/png/led_yellow.png"
                    if(gui.intBrakeTemperatureRearRight > limitYellow) return "/png/led_yellow.png"
                    return "/png/led_off.png"
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
                    if(gui.intTireWearFrontLeft < limitRed) return "/png/led_red.png"
                    if(gui.intTireWearFrontRight < limitRed) return "/png/led_red.png"
                    if(gui.intTireWearRearLeft < limitRed) return "/png/led_red.png"
                    if(gui.intTireWearRearRight < limitRed) return "/png/led_red.png"
                    var limitYellow = 50.0
                    if(gui.intTireWearFrontLeft < limitYellow) return "/png/led_yellow.png"
                    if(gui.intTireWearFrontRight < limitYellow) return "/png/led_yellow.png"
                    if(gui.intTireWearRearLeft < limitYellow) return "/png/led_yellow.png"
                    if(gui.intTireWearRearRight < limitYellow) return "/png/led_yellow.png"
                    return "/png/led_off.png"
                }
            }
        }
        Item {
            id: idItemRPMLEDs
            x: 660 * gui.guiScale
            y: 948 - sizeLEDs * gui.guiScale
            width: 600 * gui.guiScale
            height: sizeLEDs * gui.guiScale
            // the number of LEDs to be displayed
            property int countLEDs: 45
            // the RPM bandwidth to be covered by the LEDs (0-100);
            // if, for example, the bandwidth is 75, the LEDs don't
            // start lighting up until the engine RPMs are at 25%
            property int bandwidthLEDs: 75
            // internal properties
            readonly property real spaceLEDs: 2 * gui.guiScale
            readonly property real sizeLEDs: (width - (countLEDs - 1) * spaceLEDs) / countLEDs
            Repeater {
                model: idItemRPMLEDs.countLEDs
                Image {
                    x: (idItemRPMLEDs.sizeLEDs + idItemRPMLEDs.spaceLEDs) * index
                    y: 0
                    width: idItemRPMLEDs.sizeLEDs
                    height: idItemRPMLEDs.sizeLEDs
                    source: {
                        var bandwidth = idItemRPMLEDs.bandwidthLEDs
                        var bandwidthInverse = 100 - bandwidth
                        var percentageRPM = gui.intEngineRPMPercentage
                        var percentageLED = (index + 1) / idItemRPMLEDs.countLEDs * 100
                        var percentage = percentageRPM < bandwidthInverse ? 0 : (percentageRPM - bandwidthInverse) / bandwidth * 100
                        // calculate which LED color to display
                        var image
                        if(percentageLED >= 2/3 * 100) image = "/png/led_red.png"
                        else if(percentageLED >= 1/3 * 100) image = "/png/led_yellow.png"
                        else image = "/png/led_green.png"
                        // calculate whether to display the LED as ON or OFF
                        if(percentage >= percentageLED) return image
                        else return "/png/led_off.png"
                    }
                }
            }
        }
        Item {
            id: idItemLapInformation
            anchors.centerIn: parent
            width: 300 * gui.guiScale
            height: 150 * gui.guiScale
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
                font.pixelSize: 50 * gui.guiScale
                style: Text.Raised
                styleColor: Qt.rgba(0.0, 0.0, 0.0, 1.0)
            }
            Text {
                id: idTextItemLapInformationPersonalBest
                anchors.fill: parent
                anchors.topMargin: parent.height * 2 / 5
                anchors.bottomMargin: parent.height * 1 / 5
                text: "00:00:000"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 32 * gui.guiScale
                style: Text.Raised
                styleColor: Qt.rgba(0.0, 0.0, 0.0, 1.0)
            }
            Text {
                id: idTextItemLapInformationAbsoluteBest
                anchors.fill: parent
                anchors.topMargin: parent.height * 4 / 5
                text: "00:00:000"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                font.family: ApplicationStyle.fontBitwise.name
                font.pixelSize: 32 * gui.guiScale
                style: Text.Raised
                styleColor: Qt.rgba(0.0, 0.0, 0.0, 1.0)
            }
        }
        Connections {
            target: db
            onSignalLapInformation: {
                idItemLapInformationAnimations.startAnimations(_isPersonalBest, _isAbsoluteBest, _infoLapTime, _infoLapTimePersonalBest, _infoLapTimeAbsoluteBest)
            }
        }
        Item {
            id: idItemLapInformationAnimations
            readonly property real durationFadeIn: 125
            readonly property real durationFadeOut: 6375
            function startAnimations(_isPersonalBest, _isAbsoluteBest, _infoLapTime, _infoLapTimePersonalBest, _infoLapTimeAbsoluteBest) {
                // initialize lap information items
                idTextItemLapInformation.text = _infoLapTime
                idTextItemLapInformationPersonalBest.text = _infoLapTimePersonalBest
                idTextItemLapInformationAbsoluteBest.text = _infoLapTimeAbsoluteBest
                idTextItemLapInformationPersonalBest.color = _isPersonalBest ? Qt.rgba(0.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 0.0, 0.0, 1.0)
                idTextItemLapInformationAbsoluteBest.color = _isAbsoluteBest ? Qt.rgba(0.0, 1.0, 0.0, 1.0) : Qt.rgba(1.0, 0.0, 0.0, 1.0)
                // start animations
                idSequentialAnimationLap.start()
                if(_isPersonalBest) idSequentialAnimationPersonalBest.start()
                if(_isAbsoluteBest) idSequentialAnimationAbsoluteBest.start()
            }
            SequentialAnimation {
                id: idSequentialAnimationLap
                alwaysRunToEnd: true
                PropertyAnimation {
                    target: idItemLapInformation
                    properties: "opacity"
                    from: 0.0
                    to: 1.0
                    duration: idItemLapInformationAnimations.durationFadeIn
                }
                PropertyAnimation {
                    target: idItemLapInformation
                    properties: "opacity"
                    from: 1.0
                    to: 0.0
                    duration: idItemLapInformationAnimations.durationFadeOut
                }
            }
            SequentialAnimation {
                id: idSequentialAnimationPersonalBest
                alwaysRunToEnd: true
                PropertyAnimation {
                    target: idTextItemLapTimePersonalBest
                    properties: "color"
                    from: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                    to: Qt.rgba(0.0, 1.0, 0.0, 1.0)
                    duration: idItemLapInformationAnimations.durationFadeIn
                }
                PropertyAnimation {
                    target: idTextItemLapTimePersonalBest
                    properties: "color"
                    from: Qt.rgba(0.0, 1.0, 0.0, 1.0)
                    to: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                    duration: idItemLapInformationAnimations.durationFadeOut
                }
            }
            SequentialAnimation {
                id: idSequentialAnimationAbsoluteBest
                alwaysRunToEnd: true
                PropertyAnimation {
                    target: idTextItemLapTimeAbsoluteBest
                    properties: "color"
                    from: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                    to: Qt.rgba(0.0, 1.0, 0.0, 1.0)
                    duration: idItemLapInformationAnimations.durationFadeIn
                }
                PropertyAnimation {
                    target: idTextItemLapTimeAbsoluteBest
                    properties: "color"
                    from: Qt.rgba(0.0, 1.0, 0.0, 1.0)
                    to: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                    duration: idItemLapInformationAnimations.durationFadeOut
                }
            }
        }
    }
}
