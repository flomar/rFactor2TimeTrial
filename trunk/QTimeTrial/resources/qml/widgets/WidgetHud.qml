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
        // background
        Item {
            id: idItemHudBackground
            anchors.fill: parent
            property color colorBackground: Qt.rgba(0.0, 0.0, 0.0, 0.25)
            property color colorForeground: Qt.rgba(colorBackground.r, colorBackground.g, colorBackground.b, 1.0)
            Canvas {
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d")
                    // top
                    ctx.fillStyle = ApplicationStyle.hudColorBackground
                    ctx.strokeStyle = ApplicationStyle.hudColorForeground
                    ctx.lineWidth = ApplicationStyle.commonSizeBorder
                    ctx.lineJoin = "round"
                    ctx.beginPath()
                    ctx.moveTo(0 * gui.guiScale, 32 * gui.guiScale)
                    ctx.lineTo(678 * gui.guiScale, 32 * gui.guiScale)
                    ctx.lineTo(710 * gui.guiScale, 64 * gui.guiScale)
                    ctx.lineTo(1210 * gui.guiScale, 64 * gui.guiScale)
                    ctx.lineTo(1242 * gui.guiScale, 32 * gui.guiScale)
                    ctx.lineTo(1920 * gui.guiScale, 32 * gui.guiScale)
                    ctx.lineTo(1920 * gui.guiScale, 0 * gui.guiScale)
                    ctx.lineTo(0 * gui.guiScale, 0 * gui.guiScale)
                    ctx.lineTo(0 * gui.guiScale, 32 * gui.guiScale)
                    ctx.closePath()
                    ctx.fill()
                    ctx.beginPath()
                    ctx.moveTo(0 * gui.guiScale, 32 * gui.guiScale)
                    ctx.lineTo(678 * gui.guiScale, 32 * gui.guiScale)
                    ctx.lineTo(710 * gui.guiScale, 64 * gui.guiScale)
                    ctx.lineTo(1210 * gui.guiScale, 64 * gui.guiScale)
                    ctx.lineTo(1242 * gui.guiScale, 32 * gui.guiScale)
                    ctx.lineTo(1920 * gui.guiScale, 32 * gui.guiScale)
                    ctx.moveTo(1242 * gui.guiScale, 32 * gui.guiScale)
                    ctx.moveTo(1210 * gui.guiScale, 64 * gui.guiScale)
                    ctx.moveTo(710 * gui.guiScale, 64 * gui.guiScale)
                    ctx.moveTo(678 * gui.guiScale, 32 * gui.guiScale)
                    ctx.moveTo(0 * gui.guiScale, 32 * gui.guiScale)
                    ctx.closePath()
                    ctx.stroke()
                    // bottom
                    ctx.beginPath()
                    ctx.moveTo(0 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.lineTo(564 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.lineTo(660 * gui.guiScale, 952 * gui.guiScale)
                    ctx.lineTo(1260 * gui.guiScale, 952 * gui.guiScale)
                    ctx.lineTo(1356 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.lineTo(1920 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.lineTo(1920 * gui.guiScale, 1080 * gui.guiScale)
                    ctx.lineTo(0 * gui.guiScale, 1080 * gui.guiScale)
                    ctx.lineTo(0 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.closePath()
                    ctx.fill()
                    ctx.beginPath()
                    ctx.moveTo(0 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.lineTo(564 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.lineTo(660 * gui.guiScale, 952 * gui.guiScale)
                    ctx.lineTo(1260 * gui.guiScale, 952 * gui.guiScale)
                    ctx.lineTo(1356 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.lineTo(1920 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.moveTo(1356 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.moveTo(1260 * gui.guiScale, 952 * gui.guiScale)
                    ctx.moveTo(660 * gui.guiScale, 952 * gui.guiScale)
                    ctx.moveTo(564 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.moveTo(0 * gui.guiScale, 1048 * gui.guiScale)
                    ctx.closePath()
                    ctx.stroke()
                }
            }
        }
        // top (LAP, LST, DRIVER, PER, ABS)
        Item {
            id: idItemHudTop
            anchors.fill: parent
            anchors.bottomMargin: parent.height - 64 * gui.guiScale
            RowLayout {
                anchors.fill: parent
                spacing: 0
                Item {
                    id: idItemHudTopLap
                    Layout.preferredWidth: (parent.width - 564 * gui.guiScale) / 4
                    Layout.preferredHeight: parent.height
                    RowLayout {
                        anchors.fill: parent
                        anchors.topMargin: 4 * gui.guiScale
                        anchors.bottomMargin: 32 * gui.guiScale
                        spacing: 10 * gui.guiScale
                        Item {
                            id: idItemHudTopLapStatic
                            Layout.preferredWidth: parent.width * 1 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudTopLapStatic
                                text: "LAP"
                                fontColor: ApplicationStyle.hudColorTextStatic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignRight
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                        Item {
                            id: idItemHudTopLapDynamic
                            Layout.preferredWidth: parent.width * 2 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudTopLapDynamic
                                text: gui.stringLapTime
                                fontColor: ApplicationStyle.hudColorTextDynamic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignLeft
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                    }
                }
                Item {
                    id: idItemHudTopLst
                    Layout.preferredWidth: (parent.width - 564 * gui.guiScale) / 4
                    Layout.preferredHeight: parent.height
                    RowLayout {
                        anchors.fill: parent
                        anchors.topMargin: 4 * gui.guiScale
                        anchors.bottomMargin: 32 * gui.guiScale
                        spacing: 10 * gui.guiScale
                        Item {
                            id: idItemHudTopLstStatic
                            Layout.preferredWidth: parent.width * 1 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudTopLstStatic
                                text: "LST"
                                fontColor: ApplicationStyle.hudColorTextStatic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignRight
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                        Item {
                            id: idItemHudTopLstDynamic
                            Layout.preferredWidth: parent.width * 2 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudTopLstDynamic
                                text: gui.stringLapTimeLast
                                fontColor: ApplicationStyle.hudColorTextDynamic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignLeft
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                    }
                }
                Item {
                    id: idItemHudTopDriver
                    Layout.preferredWidth: 500 * gui.guiScale
                    Layout.preferredHeight: parent.height
                    Item {
                        id: idItemHudTopDriverName
                        anchors.fill: parent
                        anchors.topMargin: 4 * gui.guiScale
                        WidgetText {
                            text: gui.stringDriver
                            fontColor: ApplicationStyle.hudColorTextDynamic
                            fontPixelSize: parent.height * 0.8
                            fontHorizontalAlignment: Qt.AlignHCenter
                            fontVerticalAlignment: Qt.AlignVCenter
                        }
                    }
                }
                Item {
                    id: idItemHudTopPer
                    Layout.preferredWidth: (parent.width - 564 * gui.guiScale) / 4
                    Layout.preferredHeight: parent.height
                    RowLayout {
                        anchors.fill: parent
                        anchors.topMargin: 4 * gui.guiScale
                        anchors.bottomMargin: 32 * gui.guiScale
                        spacing: 10 * gui.guiScale
                        Item {
                            id: idItemHudTopPerDynamic
                            Layout.preferredWidth: parent.width * 2 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudTopPerDynamic
                                text: gui.stringLapTimePersonalBest
                                fontColor: ApplicationStyle.hudColorTextDynamic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignRight
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                        Item {
                            id: idItemHudTopPerStatic
                            Layout.preferredWidth: parent.width * 1 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudTopPerStatic
                                text: "PER"
                                fontColor: ApplicationStyle.hudColorTextStatic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignLeft
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                    }
                }
                Item {
                    id: idItemHudTopAbs
                    Layout.preferredWidth: (parent.width - 564 * gui.guiScale) / 4
                    Layout.preferredHeight: parent.height
                    RowLayout {
                        anchors.fill: parent
                        anchors.topMargin: 4 * gui.guiScale
                        anchors.bottomMargin: 32 * gui.guiScale
                        spacing: 10 * gui.guiScale
                        Item {
                            id: idItemHudTopAbsDynamic
                            Layout.preferredWidth: parent.width * 2 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudTopAbsDynamic
                                text: gui.stringLapTimeAbsoluteBest
                                fontColor: ApplicationStyle.hudColorTextDynamic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignRight
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                        Item {
                            id: idItemHudTopAbsStatic
                            Layout.preferredWidth: parent.width * 1 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudTopAbsStatic
                                text: "ABS"
                                fontColor: ApplicationStyle.hudColorTextStatic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignLeft
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                    }
                }
            }
        }
        // bottom (RPMLEDs)
        Item {
            id: idItemHudBottomRPMLEDs
            x: 660 * gui.guiScale
            y: 952 * gui.guiScale - 4 * gui.guiScale - sizeLEDs
            width: 600 * gui.guiScale
            height: sizeLEDs * gui.guiScale
            // the number of LEDs to be displayed
            property int countLEDs: 30
            // the RPM bandwidth to be covered by the LEDs (0-100);
            // if, for example, the bandwidth is 75, the LEDs don't
            // start lighting up until the engine RPMs are at 25%
            property int bandwidthLEDs: 75
            // internal properties
            readonly property real spaceLEDs: 2 * gui.guiScale
            readonly property real sizeLEDs: (width - (countLEDs - 1) * spaceLEDs) / countLEDs
            Repeater {
                model: idItemHudBottomRPMLEDs.countLEDs
                Image {
                    x: (idItemHudBottomRPMLEDs.sizeLEDs + idItemHudBottomRPMLEDs.spaceLEDs) * index
                    y: 0
                    width: idItemHudBottomRPMLEDs.sizeLEDs
                    height: idItemHudBottomRPMLEDs.sizeLEDs
                    source: {
                        var bandwidth = idItemHudBottomRPMLEDs.bandwidthLEDs
                        var bandwidthInverse = 100 - bandwidth
                        var percentageRPM = gui.intEngineRPMPercentage
                        var percentageLED = (index + 1) / idItemHudBottomRPMLEDs.countLEDs * 100
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
        // bottom (RPM, GEAR, SPEED, FUEL, ENGINE, BRAKES, TIRES)
        Item {
            id: idItemHudBottom
            anchors.fill: parent
            anchors.topMargin: parent.height - 128 * gui.guiScale
            RowLayout {
                anchors.fill: parent
                anchors.topMargin: 24 * gui.guiScale
                anchors.bottomMargin: 32 * gui.guiScale
                spacing: 0
                Item {
                    Layout.fillWidth: true
                }
                Item {
                    id: idItemHudBottomRPMDynamic
                    Layout.preferredWidth: parent.width * 0.15
                    Layout.preferredHeight: parent.height
                    WidgetText {
                        id: idWidgetTextHudBottomRPMDynamic
                        text: gui.intEngineRPMCurrent
                        fontColor: ApplicationStyle.hudColorTextDynamic
                        fontPixelSize: parent.height * 0.75
                        fontHorizontalAlignment: Qt.AlignRight
                        fontVerticalAlignment: Qt.AlignVCenter
                    }
                }
                Item {
                    id: idItemHudBottomGearDynamic
                    Layout.preferredWidth: parent.width * 0.15
                    Layout.preferredHeight: parent.height
                    WidgetText {
                        id: idWidgetTextHudBottomGearDynamic
                        text: gui.stringGear
                        fontColor: ApplicationStyle.hudColorTextDynamic
                        fontPixelSize: parent.height * 0.85
                        fontHorizontalAlignment: Qt.AlignHCenter
                        fontVerticalAlignment: Qt.AlignVCenter
                    }
                }
                Item {
                    id: idItemHudBottomSpeedDynamic
                    Layout.preferredWidth: parent.width * 0.15
                    Layout.preferredHeight: parent.height
                    WidgetText {
                        id: idWidgetTextHudBottomSpeedDynamic
                        text: gui.intSpeed
                        fontColor: ApplicationStyle.hudColorTextDynamic
                        fontPixelSize: parent.height * 0.75
                        fontHorizontalAlignment: Qt.AlignLeft
                        fontVerticalAlignment: Qt.AlignVCenter
                    }
                }
                Item {
                    Layout.fillWidth: true
                }
            }
            RowLayout {
                anchors.fill: parent
                spacing: 0
                Item {
                    id: idItemHudBottomFuel
                    Layout.preferredWidth: (parent.width - 792 * gui.guiScale) / 4
                    Layout.preferredHeight: parent.height
                    RowLayout {
                        anchors.fill: parent
                        anchors.topMargin: 102 * gui.guiScale
                        anchors.bottomMargin: 2 * gui.guiScale
                        spacing: 10 * gui.guiScale
                        Item {
                            id: idItemHudBottomFuelStatic
                            Layout.preferredWidth: parent.width * 2 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudBottomFuelStatic
                                text: "FUEL"
                                fontColor: ApplicationStyle.hudColorTextStatic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignRight
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                        Item {
                            id: idItemHudBottomFuelDynamic
                            Layout.preferredWidth: parent.height
                            Layout.preferredHeight: parent.height
                            Image {
                                width: parent.height
                                height: parent.height
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
                            Layout.fillWidth: true
                        }
                    }
                }
                Item {
                    id: idItemHudBottomEngine
                    Layout.preferredWidth: (parent.width - 792 * gui.guiScale) / 4
                    Layout.preferredHeight: parent.height
                    RowLayout {
                        anchors.fill: parent
                        anchors.topMargin: 100 * gui.guiScale
                        anchors.bottomMargin: 4 * gui.guiScale
                        spacing: 10 * gui.guiScale
                        Item {
                            id: idItemHudBottomEngineStatic
                            Layout.preferredWidth: parent.width * 2 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudBottomEngineStatic
                                text: "ENGINE"
                                fontColor: ApplicationStyle.hudColorTextStatic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignRight
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                        Item {
                            id: idItemHudBottomEngineDynamic
                            Layout.preferredWidth: parent.height
                            Layout.preferredHeight: parent.height
                            Image {
                                width: parent.height
                                height: parent.height
                                source: {
                                    if(gui.boolEngineOverheating) return "/png/led_red.png"
                                    return "/png/led_off.png"
                                }
                            }
                        }
                        Item {
                            Layout.fillWidth: true
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                }
                Item {
                    id: idItemHudBottomBrakes
                    Layout.preferredWidth: (parent.width - 792 * gui.guiScale) / 4
                    Layout.preferredHeight: parent.height
                    RowLayout {
                        anchors.fill: parent
                        anchors.topMargin: 100 * gui.guiScale
                        anchors.bottomMargin: 4 * gui.guiScale
                        spacing: 10 * gui.guiScale
                        Item {
                            Layout.fillWidth: true
                        }
                        Item {
                            id: idItemHudBottomBrakesDynamic
                            Layout.preferredWidth: parent.height
                            Layout.preferredHeight: parent.height
                            Image {
                                width: parent.height
                                height: parent.height
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
                            id: idItemHudBottomBrakesStatic
                            Layout.preferredWidth: parent.width * 2 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudBottomBrakesStatic
                                text: "BRAKES"
                                fontColor: ApplicationStyle.hudColorTextStatic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignLeft
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                    }
                }
                Item {
                    id: idItemHudBottomTires
                    Layout.preferredWidth: (parent.width - 792 * gui.guiScale) / 4
                    Layout.preferredHeight: parent.height
                    RowLayout {
                        anchors.fill: parent
                        anchors.topMargin: 100 * gui.guiScale
                        anchors.bottomMargin: 4 * gui.guiScale
                        spacing: 10 * gui.guiScale
                        Item {
                            Layout.fillWidth: true
                        }
                        Item {
                            id: idItemHudBottomTiresDynamic
                            Layout.preferredWidth: parent.height
                            Layout.preferredHeight: parent.height
                            Image {
                                width: parent.height
                                height: parent.height
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
                            id: idItemHudBottomTiresStatic
                            Layout.preferredWidth: parent.width * 2 / 3
                            Layout.preferredHeight: parent.height
                            WidgetText {
                                id: idWidgetTextHudBottomTiresStatic
                                text: "TIRES"
                                fontColor: ApplicationStyle.hudColorTextStatic
                                fontPixelSize: parent.height * 0.8
                                fontHorizontalAlignment: Qt.AlignLeft
                                fontVerticalAlignment: Qt.AlignVCenter
                            }
                        }
                    }
                }
            }
        }
        // bottom (CAR)
        Item {
            id: idItemHudBottomCar
            anchors.fill: parent
            anchors.topMargin: parent.height - 32 * gui.guiScale
            Item {
                id: idItemHudBottomCarName
                anchors.fill: parent
                WidgetText {
                    text: gui.stringCar
                    fontColor: ApplicationStyle.hudColorTextStatic
                    fontPixelSize: parent.height * 0.5
                    fontHorizontalAlignment: Qt.AlignHCenter
                    fontVerticalAlignment: Qt.AlignVCenter
                }
            }
        }
        // center (LAP INFORMATION)
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
                    target: idWidgetTextHudTopPerDynamic
                    properties: "fontColor"
                    to: Qt.rgba(0.0, 1.0, 0.0, 1.0)
                    duration: idItemLapInformationAnimations.durationFadeIn
                }
                PropertyAnimation {
                    target: idWidgetTextHudTopPerDynamic
                    properties: "fontColor"
                    to: ApplicationStyle.hudColorTextDynamic
                    duration: idItemLapInformationAnimations.durationFadeOut
                }
            }
            SequentialAnimation {
                id: idSequentialAnimationAbsoluteBest
                alwaysRunToEnd: true
                PropertyAnimation {
                    target: idWidgetTextHudTopAbsDynamic
                    properties: "fontColor"
                    to: Qt.rgba(0.0, 1.0, 0.0, 1.0)
                    duration: idItemLapInformationAnimations.durationFadeIn
                }
                PropertyAnimation {
                    target: idWidgetTextHudTopAbsDynamic
                    properties: "fontColor"
                    to: ApplicationStyle.hudColorTextDynamic
                    duration: idItemLapInformationAnimations.durationFadeOut
                }
            }
        }
    }
}
