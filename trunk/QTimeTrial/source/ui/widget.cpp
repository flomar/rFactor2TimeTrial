// widget.cpp

#include <ui/widget.h>

#include <application.h>

Widget::Widget(ApplicationGui *_applicationGui, const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent) :
    QWidget(_parent),
    applicationGui(_applicationGui),
    guiScale(_guiScale),
    guiFontXL(_guiFontXL),
    guiFontL(_guiFontL),
    guiFontM(_guiFontM),
    guiFontS(_guiFontS) {
    // initialize some stuff
    setMouseTracking(true);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

Widget::~Widget() {

}

ApplicationDatabase *Widget::getApplicationDatabase() {
    ApplicationDatabase *applicationDatabase = 0;
    if(applicationGui && applicationGui->getApplication()) {
        applicationDatabase = applicationGui->getApplication()->getApplicationDatabase();
    }
    return applicationDatabase;
}

void Widget::update() {
    // invoke base class implementation
    QWidget::update();
    // initialize GUI
    initializeGui();
}

void Widget::initializeGui() {
    // the default implementation doesn't do anything
}
