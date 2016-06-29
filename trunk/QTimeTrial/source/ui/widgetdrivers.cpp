// widgetdrivers.cpp

#include <ui/widgetdrivers.h>
#include "ui_widgetdrivers.h"

#include <ui/dialogcreatedriver.h>
#include <ui/dialogeditdriver.h>
#include <ui/dialogdeletedriver.h>

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

WidgetDrivers::WidgetDrivers(QWidget *_parent) :
    Widget(_parent),
    ui(new Ui::WidgetDrivers) {
    ui->setupUi(this);
    // connect signals and slots
    connect(ui->listWidgetAvailableDrivers, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotDoubleClickedListWidgetAvailableDrivers(QListWidgetItem*)));
    connect(ui->pushButtonCreateDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCreateDriver()));
    connect(ui->pushButtonEditDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonEditDriver()));
    connect(ui->pushButtonDeleteDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonDeleteDriver()));
}

WidgetDrivers::~WidgetDrivers() {
    // disconnect signals and slots
    disconnect(ui->listWidgetAvailableDrivers, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotDoubleClickedListWidgetAvailableDrivers(QListWidgetItem*)));
    disconnect(ui->pushButtonCreateDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCreateDriver()));
    disconnect(ui->pushButtonEditDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonEditDriver()));
    disconnect(ui->pushButtonDeleteDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonDeleteDriver()));
    delete ui;
}

void WidgetDrivers::update() {
    Widget::update();
    updateLineEditCurrentDriver();
    updateListWidgetAvailableDrivers();
}

void WidgetDrivers::updateLineEditCurrentDriver() {
    ui->lineEditCurrentDriver->setText("-");
    const Driver *driver = ApplicationDatabase::instance().getCurrentDriver();
    if(driver) {
        ui->lineEditCurrentDriver->setText(driver->name);
    }
}

void WidgetDrivers::updateListWidgetAvailableDrivers() {
    ui->listWidgetAvailableDrivers->clear();
    const QMap<int64_t, Driver*> &mapDrivers = ApplicationDatabase::instance().getMapDrivers();
    foreach(const Driver *driver, mapDrivers.values()) {
        if(driver) {
            ui->listWidgetAvailableDrivers->addItem(driver->name);
        }
    }
}

void WidgetDrivers::slotDoubleClickedListWidgetAvailableDrivers(QListWidgetItem *_item) {
    if(_item) {
        ApplicationDatabase::instance().setCurrentDriver(_item->text());
        update();
    }
}

void WidgetDrivers::slotPressedPushButtonCreateDriver() {
    DialogCreateDriver dialogCreateDriver;
    dialogCreateDriver.setGeometry(x(), y(), rect().width(), rect().height());
    if(dialogCreateDriver.exec() == QDialog::Accepted) {
        update();
    }
}

void WidgetDrivers::slotPressedPushButtonEditDriver() {
    if(!ui->listWidgetAvailableDrivers->currentItem()) return;
    const QString driverName = ui->listWidgetAvailableDrivers->currentItem()->text();
    if(driverName.isEmpty()) return;
    DialogEditDriver dialogEditDriver(driverName);
    dialogEditDriver.setGeometry(x(), y(), rect().width(), rect().height());
    if(dialogEditDriver.exec() == QDialog::Accepted) {
        update();
    }
}

void WidgetDrivers::slotPressedPushButtonDeleteDriver() {
    if(!ui->listWidgetAvailableDrivers->currentItem()) return;
    const QString driverName = ui->listWidgetAvailableDrivers->currentItem()->text();
    if(driverName.isEmpty()) return;
    DialogDeleteDriver dialogDeleteDriver(driverName);
    dialogDeleteDriver.setGeometry(x(), y(), rect().width(), rect().height());
    if(dialogDeleteDriver.exec() == QDialog::Accepted) {
        update();
    }
}
