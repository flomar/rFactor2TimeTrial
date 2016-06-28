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
source/ui/widget.h \
source/ui/widgetmenu.h \
source/ui/widgetabout.h \
source/ui/widgetdrivers.h \
source/ui/widgetoptions.h \
source/ui/widgetrecords.h \
../ClientServerProtocol/clientserverprotocol.h

SOURCES += \
source/main.cpp \
source/application.cpp \
source/applicationdatabase.cpp \
source/applicationgui.cpp \
source/applicationserver.cpp \
source/utilities.cpp \
source/ui/widget.cpp \
source/ui/widgetmenu.cpp \
source/ui/widgetabout.cpp \
source/ui/widgetrecords.cpp \
source/ui/widgetdrivers.cpp \
source/ui/widgetoptions.cpp \
../ClientServerProtocol/clientserverprotocol.cpp

FORMS += \
resources/ui/widgetabout.ui \
resources/ui/widgetrecords.ui \
resources/ui/widgetdrivers.ui \
resources/ui/widgetoptions.ui

RESOURCES += resources/resources.qrc

OTHER_FILES += \
resources/qml/application.qml \
resources/qml/applicationstyle.qml \
resources/qml/applicationhud.qml

OTHER_FILES += resources/qml/qmldir

OTHER_FILES += ../TODO