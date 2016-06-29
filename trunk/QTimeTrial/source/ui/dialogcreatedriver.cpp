// dialogcreatedriver.cpp

#include <ui/dialogcreatedriver.h>
#include "ui_dialogcreatedriver.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

DialogCreateDriver::DialogCreateDriver(QWidget *_parent) :
    Dialog(_parent),
    ui(new Ui::DialogCreateDriver) {
    ui->setupUi(this);
    // connect signals and slots
    connect(ui->pushButtonOK, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonOK()));
    connect(ui->pushButtonCancel, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCancel()));
}

DialogCreateDriver::~DialogCreateDriver() {
    // disconnect signals and slots
    disconnect(ui->pushButtonOK, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonOK()));
    disconnect(ui->pushButtonCancel, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCancel()));
    delete ui;
}

void DialogCreateDriver::update() {
    Dialog::update();
}

void DialogCreateDriver::slotPressedPushButtonOK() {
    if(ApplicationDatabase::instance().createDriver(ui->lineEditDriverName->text())) {
        done(QDialog::Accepted);
    }
}

void DialogCreateDriver::slotPressedPushButtonCancel() {
    done(QDialog::Rejected);
}
