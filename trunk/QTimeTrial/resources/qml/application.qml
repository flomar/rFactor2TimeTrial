// application.qml

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "."

ApplicationWindow {
    id: idApplicationWindow
    // set properties for interaction with C++ code
    property var db: QTimeTrialApplicationDatabase
    property var gui: QTimeTrialApplicationGui
    visible: gui ? gui.showHud : false
    width: gui ? gui.guiSize.x : 0
    height: gui ? gui.guiSize.y : 0
    color: "transparent"
    flags: Qt.Tool | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.WindowTransparentForInput
    title: qsTr("QTimeTrial")
    // the application HUD
    Item {
        id: idItemRoot
        anchors.fill: parent
        // fonts
        FontLoader {
            id: idFontBitwise
            source: "/fonts/Bitwise.ttf"
        }
        // HUD
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
                    font.family: idFontBitwise.name
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
                    font.family: idFontBitwise.name
                    font.pixelSize: 20 * gui.guiScale
                }
            }
            Item {
                id: idItemDriver
                x: 810 * gui.guiScale
                y: 8 * gui.guiScale
                width: 300 * gui.guiScale
                height: 40 * gui.guiScale
                Text {
                    id: idTextItemDriver
                    anchors.fill: parent
                    text: gui.stringDriver
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                    font.family: idFontBitwise.name
                    font.pixelSize: 36 * gui.guiScale
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
                    font.family: idFontBitwise.name
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
                    font.family: idFontBitwise.name
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
                    font.family: idFontBitwise.name
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
                    font.family: idFontBitwise.name
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
                    font.family: idFontBitwise.name
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
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 0) return "/png/led_green.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 1
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 1) return "/png/led_green.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 2
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 2) return "/png/led_green.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 3
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 3) return "/png/led_green.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 4
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 4) return "/png/led_green.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 5
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 5) return "/png/led_green.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 6
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 6) return "/png/led_green.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 7
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 7) return "/png/led_green.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 8
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 8) return "/png/led_green.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 9
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 9) return "/png/led_green.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 10
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 10) return "/png/led_yellow.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 11
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 11) return "/png/led_yellow.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 12
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 12) return "/png/led_yellow.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 13
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 13) return "/png/led_yellow.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 14
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 14) return "/png/led_yellow.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 15
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 15) return "/png/led_yellow.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 16
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 16) return "/png/led_yellow.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 17
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 17) return "/png/led_yellow.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 18
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 18) return "/png/led_yellow.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 19
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 19) return "/png/led_yellow.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 20
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 20) return "/png/led_red.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 21
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 21) return "/png/led_red.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 22
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 22) return "/png/led_red.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 23
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 23) return "/png/led_red.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 24
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 24) return "/png/led_red.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 25
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 25) return "/png/led_red.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 26
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 26) return "/png/led_red.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 27
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 27) return "/png/led_red.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 28
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 28) return "/png/led_red.png"
                        return "/png/led_off.png"
                    }
                }
                Image {
                    x: 20 * gui.guiScale * 29
                    y: 0
                    width: 16 * gui.guiScale
                    height: 16 * gui.guiScale
                    source: {
                        if(gui.intEngineRPMPercentage >= 50 + 50 / 30 * 29) return "/png/led_red.png"
                        return "/png/led_off.png"
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
                    font.family: idFontBitwise.name
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
                    font.family: idFontBitwise.name
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
                    font.family: idFontBitwise.name
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
}
