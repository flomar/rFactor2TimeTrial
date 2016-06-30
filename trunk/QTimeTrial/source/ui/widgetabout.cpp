// widgetabout.cpp

#include <ui/widgetabout.h>
#include "ui_widgetabout.h"

#include <application.h>
#include <applicationgui.h>
#include <applicationdatabase.h>

#include <utilities.h>

WidgetAbout::WidgetAbout(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent) :
    Widget(_guiScale, _guiFontXL, _guiFontL, _guiFontM, _guiFontS, _parent),
    ui(new Ui::WidgetAbout) {
    ui->setupUi(this);
    // initialize user interface
    ui->labelApplicationName->setText(APPLICATION_NAME);
    ui->labelApplicationCopyright->setText(APPLICATION_COPYRIGHT);
}

WidgetAbout::~WidgetAbout() {
    delete ui;
}

void WidgetAbout::update() {
    Widget::update();
}

void WidgetAbout::initializeGui() {
    Widget::initializeGui();
    // initialize GUI elements
    ui->labelTitle->setFont(guiFontXL);
    ui->labelApplicationName->setFont(guiFontL);
    ui->labelApplicationCopyright->setFont(guiFontM);
}
