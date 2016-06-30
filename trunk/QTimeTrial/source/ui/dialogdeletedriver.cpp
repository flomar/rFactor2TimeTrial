// dialogdeletedriver.cpp

#include <ui/dialogdeletedriver.h>
#include "ui_dialogdeletedriver.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

DialogDeleteDriver::DialogDeleteDriver(const QString &_driverName, const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent) :
    Dialog(_guiScale, _guiFontXL, _guiFontL, _guiFontM, _guiFontS, _parent),
    ui(new Ui::DialogDeleteDriver),
    driverName(_driverName) {
    ui->setupUi(this);
    // connect signals and slots
    connect(ui->pushButtonOK, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonOK()));
    connect(ui->pushButtonCancel, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCancel()));
    // initialize user interface
    ui->lineEditDriverName->setText(driverName);
}

DialogDeleteDriver::~DialogDeleteDriver() {
    // disconnect signals and slots
    disconnect(ui->pushButtonOK, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonOK()));
    disconnect(ui->pushButtonCancel, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCancel()));
    delete ui;
}

void DialogDeleteDriver::update() {
    Dialog::update();
}

void DialogDeleteDriver::initializeGui() {
    Dialog::initializeGui();
    // initialize GUI elements
    // TODO/FIXME
}

void DialogDeleteDriver::slotPressedPushButtonOK() {
    if(ApplicationDatabase::instance().deleteDriver(driverName)) {
        done(QDialog::Accepted);
    }
}

void DialogDeleteDriver::slotPressedPushButtonCancel() {
    done(QDialog::Rejected);
}
