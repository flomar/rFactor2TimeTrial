// widget.cpp

#include <ui/widget.h>

#include <utilities.h>

Widget::Widget(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent) :
    QWidget(_parent),
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

void Widget::update() {
    // invoke base class implementation
    QWidget::update();
    // initialize GUI
    initializeGui();
}

void Widget::initializeGui() {
    // the default implementation doesn't do anything
}
