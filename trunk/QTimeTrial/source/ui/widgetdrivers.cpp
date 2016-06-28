// widgetdrivers.cpp

#include <ui/widgetdrivers.h>
#include "ui_widgetdrivers.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

WidgetDrivers::WidgetDrivers(QWidget *parent) :
    Widget(parent),
    ui(new Ui::WidgetDrivers) {
    ui->setupUi(this);
    // connect signals and slots
    connect(ui->listWidgetAvailableDrivers, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotDoubleClickedListWidgetAvailableDrivers(QListWidgetItem*)));
    connect(ui->pushButtonCreateDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCreateDriver()));
    connect(ui->pushButtonSetCurrentDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonSetCurrentDriver()));
    connect(ui->pushButtonDeleteDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonDeleteDriver()));
}

WidgetDrivers::~WidgetDrivers() {
    // disconnect signals and slots
    disconnect(ui->listWidgetAvailableDrivers, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotDoubleClickedListWidgetAvailableDrivers(QListWidgetItem*)));
    disconnect(ui->pushButtonCreateDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonCreateDriver()));
    disconnect(ui->pushButtonSetCurrentDriver, SIGNAL(pressed()), this, SLOT(slotPressedPushButtonSetCurrentDriver()));
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
    qDebug() << "TODO/FIXME: WidgetDrivers::slotPressedPushButtonCreateDriver";
}

void WidgetDrivers::slotPressedPushButtonSetCurrentDriver() {
    if(ui->listWidgetAvailableDrivers->currentRow() != -1) {
        const QListWidgetItem *currentItem = ui->listWidgetAvailableDrivers->currentItem();
        if(currentItem) {
            ApplicationDatabase::instance().setCurrentDriver(currentItem->text());
            update();
        }
    }
}

void WidgetDrivers::slotPressedPushButtonDeleteDriver() {
    qDebug() << "TODO/FIXME: WidgetDrivers::slotPressedPushButtonDeleteDriver";
}
