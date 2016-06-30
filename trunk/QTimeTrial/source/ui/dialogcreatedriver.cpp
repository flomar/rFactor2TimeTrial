// dialogcreatedriver.cpp

#include <ui/dialogcreatedriver.h>
#include "ui_dialogcreatedriver.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

DialogCreateDriver::DialogCreateDriver(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent) :
    Dialog(_guiScale, _guiFontXL, _guiFontL, _guiFontM, _guiFontS, _parent),
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
    // TODO/FIXME
}

void DialogCreateDriver::slotPressedPushButtonOK() {
    if(ApplicationDatabase::instance().createDriver(ui->lineEditDriverName->text())) {
        done(QDialog::Accepted);
    }
}

void DialogCreateDriver::slotPressedPushButtonCancel() {
    done(QDialog::Rejected);
}
