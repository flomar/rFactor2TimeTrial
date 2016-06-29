// dialog.cpp

#include <ui/dialog.h>

#include <utilities.h>

Dialog::Dialog(QWidget *_parent) :
    QDialog(_parent) {
    // initialize some stuff
    setMouseTracking(true);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

Dialog::~Dialog() {

}

void Dialog::update() {
    // the default implementation doesn't do anything
    QDialog::update();
}
