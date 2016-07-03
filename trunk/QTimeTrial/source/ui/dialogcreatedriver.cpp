// dialogcreatedriver.cpp

#include <ui/dialogcreatedriver.h>
#include "ui_dialogcreatedriver.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

DialogCreateDriver::DialogCreateDriver(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS) :
    Dialog(_guiScale, _guiFontXL, _guiFontL, _guiFontM, _guiFontS),
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

void DialogCreateDriver::initializeGui() {
    Dialog::initializeGui();
    // initialize GUI elements
    ui->labelTitle->setFont(guiFontXL);
    ui->groupBoxDriverName->setFont(guiFontM);
    ui->lineEditDriverName->setFont(guiFontM);
    ui->pushButtonOK->setFont(guiFontM);
    ui->pushButtonCancel->setFont(guiFontM);
}

void DialogCreateDriver::slotPressedPushButtonOK() {
    if(ui->lineEditDriverName->text().isEmpty()) return;
    done(QDialog::Accepted);
}

void DialogCreateDriver::slotPressedPushButtonCancel() {
    done(QDialog::Rejected);
}

QString DialogCreateDriver::getDriverName() const {
    return ui->lineEditDriverName->text();
}
