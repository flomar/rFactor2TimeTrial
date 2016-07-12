TARGET = QTimeTrial

QT += core gui sql quick quickwidgets widgets

CONFIG += c++11
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += source

HEADERS += \
source/main.h \
source/application.h \
source/applicationdatabase.h \
source/applicationgui.h \
source/applicationserver.h \
source/utilities.h \
../Common/clientserverprotocol.h

SOURCES += \
source/main.cpp \
source/application.cpp \
source/applicationdatabase.cpp \
source/applicationgui.cpp \
source/applicationserver.cpp \
source/utilities.cpp \
../Common/clientserverprotocol.cpp

RESOURCES += \
resources/resources.qrc

OTHER_FILES += \
resources/qml/application.qml \
resources/qml/applicationstyle.qml \
resources/qml/widgets/Widget.qml \
resources/qml/widgets/WidgetMenu.qml \
resources/qml/widgets/WidgetAbout.qml \
resources/qml/widgets/WidgetDrivers.qml \
resources/qml/widgets/WidgetRecords.qml \
resources/qml/widgets/WidgetOptions.qml \
resources/qml/widgets/WidgetHud.qml \
resources/qml/components/WidgetTitle.qml \
resources/qml/components/WidgetText.qml \
resources/qml/components/WidgetTextInput.qml \
resources/qml/components/WidgetCheckBox.qml \
resources/qml/components/WidgetButton.qml \
resources/qml/qmldir

OTHER_FILES += \
../../README.md
