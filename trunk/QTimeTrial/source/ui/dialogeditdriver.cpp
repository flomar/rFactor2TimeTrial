// dialogeditdriver.cpp

#include <ui/dialogeditdriver.h>
#include "ui_dialogeditdriver.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

DialogEditDriver::DialogEditDriver(QWidget *_parent) :
    Dialog(_parent),
    ui(new Ui::DialogEditDriver) {
    ui->setupUi(this);
    // connect signals and slots
    connect(ui->pushButtonOK, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonOK()));
    connect(ui->pushButtonCancel, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCancel()));
}

DialogEditDriver::~DialogEditDriver() {
    // disconnect signals and slots
    disconnect(ui->pushButtonOK, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonOK()));
    disconnect(ui->pushButtonCancel, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCancel()));
    delete ui;
}

void DialogEditDriver::update() {
    Dialog::update();
}

void DialogEditDriver::slotPressedPushButtonOK() {
    done(QDialog::Accepted);
}

void DialogEditDriver::slotPressedPushButtonCancel() {
    done(QDialog::Rejected);
}
