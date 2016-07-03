// widgetdrivers.cpp

#include <ui/widgetdrivers.h>
#include "ui_widgetdrivers.h"

#include <application.h>

#include <ui/dialogcreatedriver.h>
#include <ui/dialogeditdriver.h>
#include <ui/dialogdeletedriver.h>

WidgetDrivers::WidgetDrivers(ApplicationGui *_applicationGui, const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent) :
    Widget(_applicationGui, _guiScale, _guiFontXL, _guiFontL, _guiFontM, _guiFontS, _parent),
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

void WidgetDrivers::initializeGui() {
    Widget::initializeGui();
    // initialize GUI elements
    ui->labelTitle->setFont(guiFontXL);
    ui->groupBoxAvailableDrivers->setFont(guiFontM);
    ui->listWidgetAvailableDrivers->setFont(guiFontM);
    ui->groupBoxCurrentDriver->setFont(guiFontM);
    ui->lineEditCurrentDriver->setFont(guiFontM);
    ui->pushButtonCreateDriver->setFont(guiFontM);
    ui->pushButtonEditDriver->setFont(guiFontM);
    ui->pushButtonDeleteDriver->setFont(guiFontM);
}

void WidgetDrivers::updateLineEditCurrentDriver() {
    // acquire a pointer to the application database
    const ApplicationDatabase *applicationDatabase = getApplicationDatabase();
    if(!applicationDatabase) return;
    // update current driver
    ui->lineEditCurrentDriver->setText("-");
    const Driver *driver = applicationDatabase->getCurrentDriver();
    if(driver) {
        ui->lineEditCurrentDriver->setText(driver->name);
    }
}

void WidgetDrivers::updateListWidgetAvailableDrivers() {
    // acquire a pointer to the application database
    const ApplicationDatabase *applicationDatabase = getApplicationDatabase();
    if(!applicationDatabase) return;
    // update available drivers
    ui->listWidgetAvailableDrivers->clear();
    const QMap<int64_t, Driver*> &mapDrivers = applicationDatabase->getMapDrivers();
    foreach(const Driver *driver, mapDrivers.values()) {
        if(driver) {
            ui->listWidgetAvailableDrivers->addItem(driver->name);
        }
    }
}

void WidgetDrivers::slotDoubleClickedListWidgetAvailableDrivers(QListWidgetItem *_item) {
    // acquire a pointer to the application database
    ApplicationDatabase *applicationDatabase = getApplicationDatabase();
    if(!applicationDatabase) return;
    // set the current driver
    if(_item) {
        applicationDatabase->setCurrentDriver(_item->text());
        update();
    }
}

void WidgetDrivers::slotPressedPushButtonCreateDriver() {
    // acquire a pointer to the application database
    ApplicationDatabase *applicationDatabase = getApplicationDatabase();
    if(!applicationDatabase) return;
    // fire up the dialog
    DialogCreateDriver dialogCreateDriver(guiScale, guiFontXL, guiFontL, guiFontM, guiFontS);
    dialogCreateDriver.setGeometry(x(), y(), rect().width(), rect().height());
    if(dialogCreateDriver.exec() == QDialog::Accepted) {
        if(applicationDatabase->createDriver(dialogCreateDriver.getDriverName())) {
            update();
        }
    }
}

void WidgetDrivers::slotPressedPushButtonEditDriver() {
    // acquire a pointer to the application database
    ApplicationDatabase *applicationDatabase = getApplicationDatabase();
    if(!applicationDatabase) return;
    // fire up the dialog
    if(!ui->listWidgetAvailableDrivers->currentItem()) return;
    const QString driverName = ui->listWidgetAvailableDrivers->currentItem()->text();
    if(driverName.isEmpty()) return;
    DialogEditDriver dialogEditDriver(driverName, guiScale, guiFontXL, guiFontL, guiFontM, guiFontS);
    dialogEditDriver.setGeometry(x(), y(), rect().width(), rect().height());
    if(dialogEditDriver.exec() == QDialog::Accepted) {
        update();
    }
}

void WidgetDrivers::slotPressedPushButtonDeleteDriver() {
    // acquire a pointer to the application database
    ApplicationDatabase *applicationDatabase = getApplicationDatabase();
    if(!applicationDatabase) return;
    // fire up the dialog
    if(!ui->listWidgetAvailableDrivers->currentItem()) return;
    const QString driverName = ui->listWidgetAvailableDrivers->currentItem()->text();
    if(driverName.isEmpty()) return;
    DialogDeleteDriver dialogDeleteDriver(driverName, guiScale, guiFontXL, guiFontL, guiFontM, guiFontS);
    dialogDeleteDriver.setGeometry(x(), y(), rect().width(), rect().height());
    if(dialogDeleteDriver.exec() == QDialog::Accepted) {
        if(applicationDatabase->deleteDriver(dialogDeleteDriver.getDriverName())) {
            update();
        }
    }
}
