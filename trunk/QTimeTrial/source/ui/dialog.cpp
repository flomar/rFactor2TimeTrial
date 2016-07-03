// dialog.cpp

#include <ui/dialog.h>

#include <utilities.h>

Dialog::Dialog(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS) :
    guiScale(_guiScale),
    guiFontXL(_guiFontXL),
    guiFontL(_guiFontL),
    guiFontM(_guiFontM),
    guiFontS(_guiFontS) {
    // initialize some stuff
    setMouseTracking(true);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

Dialog::~Dialog() {

}

int Dialog::exec() {
    // initial update
    update();
    // invoke base class implementation
    return QDialog::exec();
}

void Dialog::update() {
    // invoke base class implementation
    QDialog::update();
    // initialize GUI
    initializeGui();
}

void Dialog::initializeGui() {
    // the default implementation doesn't do anything
}
