// widgetrecords.cpp

#include <ui/widgetrecords.h>
#include "ui_widgetrecords.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

WidgetRecords::WidgetRecords(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent) :
    Widget(_guiScale, _guiFontXL, _guiFontL, _guiFontM, _guiFontS, _parent),
    ui(new Ui::WidgetRecords) {
    ui->setupUi(this);
    // connect signals and slots
    connect(ui->comboBoxLimit, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangedCurrentIndexComboBoxLimit(int)));
    connect(ui->comboBoxDriver, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangedCurrentIndexComboBoxDriver(int)));
    connect(ui->comboBoxCar, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangedCurrentIndexComboBoxCar(int)));
    connect(ui->comboBoxFrontTireCompound, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangedCurrentIndexComboBoxFrontTireCompound(int)));
    connect(ui->comboBoxRearTireCompound, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangedCurrentIndexComboBoxRearTireCompound(int)));
}

WidgetRecords::~WidgetRecords() {
    // disconnect signals and slots
    disconnect(ui->comboBoxLimit, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangedCurrentIndexComboBoxLimit(int)));
    disconnect(ui->comboBoxDriver, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangedCurrentIndexComboBoxDriver(int)));
    disconnect(ui->comboBoxCar, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangedCurrentIndexComboBoxCar(int)));
    disconnect(ui->comboBoxFrontTireCompound, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangedCurrentIndexComboBoxFrontTireCompound(int)));
    disconnect(ui->comboBoxRearTireCompound, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangedCurrentIndexComboBoxRearTireCompound(int)));
    delete ui;
}

void WidgetRecords::update() {
    Widget::update();
    // acquire data (and store it temporarily)
    trackName = ApplicationDatabase::instance().getCurrentTrackName();
    vectorRecordsUnsortedAndUnfiltered = ApplicationDatabase::instance().getVectorRecordsUnsortedAndUnfiltered();
    // update user interface
    updateTableViewAvailableRecords();
    updateComboBoxes();
}

void WidgetRecords::initializeGui() {
    Widget::initializeGui();
    // initialize GUI elements
    ui->labelTitle->setFont(guiFontXL);
    ui->groupBoxAvailableRecords->setFont(guiFontM);
    ui->tableWidgetAvailableRecords->setFont(guiFontM);
    ui->groupBoxFilters->setFont(guiFontM);
    ui->comboBoxLimit->setFont(guiFontM);
    ui->comboBoxDriver->setFont(guiFontM);
    ui->comboBoxCar->setFont(guiFontM);
    ui->comboBoxFrontTireCompound->setFont(guiFontM);
    ui->comboBoxRearTireCompound->setFont(guiFontM);
    // initialize GUI elements
    ui->tableWidgetAvailableRecords->setColumnWidth(0, 75 * guiScale);
    ui->tableWidgetAvailableRecords->setColumnWidth(1, 150 * guiScale);
    ui->tableWidgetAvailableRecords->setColumnWidth(2, 150 * guiScale);
    ui->tableWidgetAvailableRecords->setColumnWidth(3, 330 * guiScale);
    ui->tableWidgetAvailableRecords->setColumnWidth(4, 150 * guiScale);
}

void WidgetRecords::updateTableViewAvailableRecords() {
    while(ui->tableWidgetAvailableRecords->rowCount() > 0)
        ui->tableWidgetAvailableRecords->removeRow(0);
    const QVector<Record> vectorRecords = calculateVectorRecords();
    foreach(const Record record, vectorRecords) {
        const int rowIndex = ui->tableWidgetAvailableRecords->rowCount();
        QTableWidgetItem *itemRank = new QTableWidgetItem();
        if(!itemRank) continue;
        itemRank->setText(QString("#%1").arg(record.rank));
        QTableWidgetItem *itemTime = new QTableWidgetItem();
        if(!itemTime) continue;
        itemTime->setText(QString("%1").arg(record.timeHumanReadable));
        QTableWidgetItem *itemDriver = new QTableWidgetItem();
        if(!itemDriver) continue;
        itemDriver->setText(QString("%1").arg(record.driver));
        QTableWidgetItem *itemCar = new QTableWidgetItem();
        if(!itemCar) continue;
        itemCar->setText(QString("%1").arg(record.car));
        QTableWidgetItem *itemDate = new QTableWidgetItem();
        if(!itemDate) continue;
        itemDate->setText(QString("%1").arg(record.dateHumanReadable));
        ui->tableWidgetAvailableRecords->insertRow(rowIndex);
        ui->tableWidgetAvailableRecords->setItem(rowIndex, 0, itemRank);
        ui->tableWidgetAvailableRecords->setItem(rowIndex, 1, itemTime);
        ui->tableWidgetAvailableRecords->setItem(rowIndex, 2, itemDriver);
        ui->tableWidgetAvailableRecords->setItem(rowIndex, 3, itemCar);
        ui->tableWidgetAvailableRecords->setItem(rowIndex, 4, itemDate);
    }
}

void WidgetRecords::updateComboBoxes() {
    // delete all combo box entries except for the first one in each box,
    // but ignore the limit box since its content is static
    while(ui->comboBoxDriver->count() > 1)
        ui->comboBoxDriver->removeItem(ui->comboBoxDriver->count() - 1);
    while(ui->comboBoxCar->count() > 1)
        ui->comboBoxCar->removeItem(ui->comboBoxCar->count() - 1);
    while(ui->comboBoxFrontTireCompound->count() > 1)
        ui->comboBoxFrontTireCompound->removeItem(ui->comboBoxFrontTireCompound->count() - 1);
    while(ui->comboBoxRearTireCompound->count() > 1)
        ui->comboBoxRearTireCompound->removeItem(ui->comboBoxRearTireCompound->count() - 1);
    // go through temporary data and extract what we need
    QSet<QString> setDrivers;
    QSet<QString> setCars;
    QSet<QString> setFrontTireCompounds;
    QSet<QString> setRearTireCompounds;
    foreach(const Record record, vectorRecordsUnsortedAndUnfiltered) {
        if(trackName != record.track) continue;
        setDrivers.insert(record.driver);
        setCars.insert(record.car);
        setFrontTireCompounds.insert(record.frontTireCompound);
        setRearTireCompounds.insert(record.rearTireCompound);
    }
    // fill the combo boxes
    foreach(const QString driver, setDrivers) {
        ui->comboBoxDriver->insertItem(ui->comboBoxDriver->count(), driver);
    }
    foreach(const QString car, setCars) {
        ui->comboBoxCar->insertItem(ui->comboBoxCar->count(), car);
    }
    foreach(const QString frontTireCompound, setFrontTireCompounds) {
        ui->comboBoxFrontTireCompound->insertItem(ui->comboBoxFrontTireCompound->count(), frontTireCompound);
    }
    foreach(const QString rearTireCompound, setRearTireCompounds) {
        ui->comboBoxRearTireCompound->insertItem(ui->comboBoxRearTireCompound->count(), rearTireCompound);
    }
    // select the very first entry in each combo box
    ui->comboBoxLimit->setCurrentIndex(0);
    ui->comboBoxDriver->setCurrentIndex(0);
    ui->comboBoxCar->setCurrentIndex(0);
    ui->comboBoxFrontTireCompound->setCurrentIndex(0);
    ui->comboBoxRearTireCompound->setCurrentIndex(0);
}

void WidgetRecords::slotChangedCurrentIndexComboBoxLimit(const int _index) {
    Q_UNUSED(_index);
    updateTableViewAvailableRecords();
}

void WidgetRecords::slotChangedCurrentIndexComboBoxDriver(const int _index) {
    Q_UNUSED(_index);
    updateTableViewAvailableRecords();
}

void WidgetRecords::slotChangedCurrentIndexComboBoxCar(const int _index) {
    Q_UNUSED(_index);
    updateTableViewAvailableRecords();
}

void WidgetRecords::slotChangedCurrentIndexComboBoxFrontTireCompound(const int _index) {
    Q_UNUSED(_index);
    updateTableViewAvailableRecords();
}

void WidgetRecords::slotChangedCurrentIndexComboBoxRearTireCompound(const int _index) {
    Q_UNUSED(_index);
    updateTableViewAvailableRecords();
}

QVector<Record> WidgetRecords::calculateVectorRecords() const {
    // the result variable
    QVector<Record> vectorRecords;
    // acquire combo box settings-- if an integer is zero or if a
    // string is empty, there is no filter applied in that area
    const int limit = ui->comboBoxLimit->currentIndex() != 0 ? ui->comboBoxLimit->currentText().toInt() : 0;
    const QString driver = ui->comboBoxDriver->currentIndex() != 0 ? ui->comboBoxDriver->currentText() : QString::null;
    const QString car = ui->comboBoxCar->currentIndex() != 0 ? ui->comboBoxCar->currentText() : QString::null;
    const QString frontTireCompound = ui->comboBoxFrontTireCompound->currentIndex() != 0 ? ui->comboBoxFrontTireCompound->currentText() : QString::null;
    const QString rearTireCompound = ui->comboBoxRearTireCompound->currentIndex() != 0 ? ui->comboBoxRearTireCompound->currentText() : QString::null;
    // go through temporary data and extract what we need
    foreach(const Record record, vectorRecordsUnsortedAndUnfiltered) {
        if(!driver.isEmpty() && driver != record.driver) continue;
        if(!car.isEmpty() && car != record.car) continue;
        if(!frontTireCompound.isEmpty() && frontTireCompound != record.frontTireCompound) continue;
        if(!rearTireCompound.isEmpty() && rearTireCompound != record.rearTireCompound) continue;
        if(trackName != record.track) continue;
        vectorRecords.push_back(record);
    }
    // sort the records
    qSort(vectorRecords.begin(), vectorRecords.end(), Record::lessThan);
    // limit the records if necessary
    if(limit > 0) {
        while(vectorRecords.size() > limit) {
            vectorRecords.pop_back();
        }
    }
    // sanitize records (set ranks and human-readable times and dates)
    QVector<Record> vectorRecordsRanked;
    foreach(const Record record, vectorRecords) {
        Record recordRanked = record;
        recordRanked.rank = vectorRecordsRanked.size() + 1;
        recordRanked.timeHumanReadable = Utilities::Core::timeInMillisecondsToStringInMinutesSecondsMilliseconds(recordRanked.time);
        recordRanked.dateHumanReadable = Utilities::Core::timeInMillisecondsToStringDate(recordRanked.date);
        vectorRecordsRanked.push_back(recordRanked);
    }
    vectorRecords = vectorRecordsRanked;
    return vectorRecords;
}
