// dialogdeletedriver.cpp

#include <ui/dialogdeletedriver.h>
#include "ui_dialogdeletedriver.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

DialogDeleteDriver::DialogDeleteDriver(const QString &_driverName, QWidget *_parent) :
    Dialog(_parent),
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

void DialogDeleteDriver::slotPressedPushButtonOK() {
    if(ApplicationDatabase::instance().deleteDriver(driverName)) {
        done(QDialog::Accepted);
    }
}

void DialogDeleteDriver::slotPressedPushButtonCancel() {
    done(QDialog::Rejected);
}
