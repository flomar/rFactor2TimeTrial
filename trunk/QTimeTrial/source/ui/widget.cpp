// widget.cpp

#include <ui/widget.h>

#include <utilities.h>

Widget::Widget(QWidget *_parent) :
    QWidget(_parent) {
    // initialize some stuff
    setMouseTracking(true);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

Widget::~Widget() {

}

void Widget::update() {
    // the default implementation doesn't do anything
    QWidget::update();
}
