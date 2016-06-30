// dialogeditdriver.cpp

#include <ui/dialogeditdriver.h>
#include "ui_dialogeditdriver.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

DialogEditDriver::DialogEditDriver(const QString &_driverName, const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent) :
    Dialog(_guiScale, _guiFontXL, _guiFontL, _guiFontM, _guiFontS, _parent),
    ui(new Ui::DialogEditDriver),
    driverName(_driverName) {
    ui->setupUi(this);
    // connect signals and slots
    connect(ui->pushButtonOK, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonOK()));
    connect(ui->pushButtonCancel, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCancel()));
    // initialize user interface
    ui->lineEditDriverName->setText(driverName);
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

void DialogEditDriver::initializeGui() {
    Dialog::initializeGui();
    // initialize GUI elements
    ui->labelTitle->setFont(guiFontXL);
    ui->groupBoxDriverName->setFont(guiFontM);
    ui->lineEditDriverName->setFont(guiFontM);
    ui->pushButtonOK->setFont(guiFontM);
    ui->pushButtonCancel->setFont(guiFontM);
}

void DialogEditDriver::slotPressedPushButtonOK() {
    done(QDialog::Accepted);
}

void DialogEditDriver::slotPressedPushButtonCancel() {
    done(QDialog::Rejected);
}
