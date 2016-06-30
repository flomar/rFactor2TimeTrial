// widgetoptions.cpp

#include <ui/widgetoptions.h>
#include "ui_widgetoptions.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

WidgetOptions::WidgetOptions(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent) :
    Widget(_guiScale, _guiFontXL, _guiFontL, _guiFontM, _guiFontS, _parent),
    ui(new Ui::WidgetOptions) {
    ui->setupUi(this);
    // connect signals and slots
    connect(ui->checkBoxAutoDeleteSessions, SIGNAL(toggled(bool)), this, SLOT(slotToggledCheckBoxAutoDeleteSessions(bool)));
    connect(ui->checkBoxAutoDeleteRuns, SIGNAL(toggled(bool)), this, SLOT(slotToggledCheckBoxAutoDeleteRuns(bool)));
    connect(ui->checkBoxAutoDeleteLaps, SIGNAL(toggled(bool)), this, SLOT(slotToggledCheckBoxAutoDeleteLaps(bool)));
}

WidgetOptions::~WidgetOptions() {
    // disconnect signals and slots
    disconnect(ui->checkBoxAutoDeleteSessions, SIGNAL(toggled(bool)), this, SLOT(slotToggledCheckBoxAutoDeleteSessions(bool)));
    disconnect(ui->checkBoxAutoDeleteRuns, SIGNAL(toggled(bool)), this, SLOT(slotToggledCheckBoxAutoDeleteRuns(bool)));
    disconnect(ui->checkBoxAutoDeleteLaps, SIGNAL(toggled(bool)), this, SLOT(slotToggledCheckBoxAutoDeleteLaps(bool)));
    delete ui;
}

void WidgetOptions::update() {
    Widget::update();
    updateCheckBoxes();
}

void WidgetOptions::initializeGui() {
    Widget::initializeGui();
    // initialize GUI elements
    ui->labelTitle->setFont(guiFontXL);
    ui->groupBoxDatabase->setFont(guiFontM);
    ui->checkBoxAutoDeleteSessions->setFont(guiFontM);
    ui->checkBoxAutoDeleteRuns->setFont(guiFontM);
    ui->checkBoxAutoDeleteLaps->setFont(guiFontM);
}

void WidgetOptions::updateCheckBoxes() {
    const QMap<int64_t, Options*> &mapOptions = ApplicationDatabase::instance().getMapOptions();
    if(!mapOptions.isEmpty()) {
        const Options *options = mapOptions.values().first();
        if(options) {
            ui->checkBoxAutoDeleteSessions->setChecked(options->autoDeleteSessions == 1);
            ui->checkBoxAutoDeleteRuns->setChecked(options->autoDeleteRuns == 1);
            ui->checkBoxAutoDeleteLaps->setChecked(options->autoDeleteLaps == 1);
        }
    }
}

void WidgetOptions::slotToggledCheckBoxAutoDeleteSessions(const bool _checked) {
    const QMap<int64_t, Options*> &mapOptions = ApplicationDatabase::instance().getMapOptions();
    if(!mapOptions.isEmpty()) {
        Options *options = mapOptions.values().first();
        if(options) {
            options->autoDeleteSessions = _checked ? 1 : 0;
        }
    }
}

void WidgetOptions::slotToggledCheckBoxAutoDeleteRuns(const bool _checked) {
    const QMap<int64_t, Options*> &mapOptions = ApplicationDatabase::instance().getMapOptions();
    if(!mapOptions.isEmpty()) {
        Options *options = mapOptions.values().first();
        if(options) {
            options->autoDeleteRuns = _checked ? 1 : 0;
        }
    }
}

void WidgetOptions::slotToggledCheckBoxAutoDeleteLaps(const bool _checked) {
    const QMap<int64_t, Options*> &mapOptions = ApplicationDatabase::instance().getMapOptions();
    if(!mapOptions.isEmpty()) {
        Options *options = mapOptions.values().first();
        if(options) {
            options->autoDeleteLaps = _checked ? 1 : 0;
        }
    }
}
