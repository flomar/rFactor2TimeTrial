// widget.cpp

#include <ui/widget.h>

#include <utilities.h>

Widget::Widget(QWidget *_parent) :
    QWidget(_parent),
    colorWidgetBackground(QColor(0, 0, 0, 255)),
    colorWidgetBorder(QColor(255, 255, 255, 255)),
    colorButtonBackground(QColor(0, 0, 0, 255)),
    colorButtonBackgroundHovered(QColor(25, 25, 25, 255)),
    colorButtonBorder(QColor(255, 255, 255, 255)),
    colorButtonBorderHovered(QColor(255, 255, 0, 255)),
    colorButtonText(QColor(255, 255, 255, 255)),
    colorButtonTextHovered(QColor(255, 255, 0, 255)) {
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
