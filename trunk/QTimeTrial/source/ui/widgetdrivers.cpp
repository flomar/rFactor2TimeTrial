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
    dialogCreateDriver.setGeometry(rect());
    dialogCreateDriver.exec();
}

void WidgetDrivers::slotPressedPushButtonEditDriver() {
    DialogEditDriver dialogEditDriver;
    dialogEditDriver.setGeometry(rect());
    dialogEditDriver.exec();
}

void WidgetDrivers::slotPressedPushButtonDeleteDriver() {
    DialogDeleteDriver dialogDeleteDriver;
    dialogDeleteDriver.setGeometry(rect());
    dialogDeleteDriver.exec();
}
