// widgetabout.cpp

#include <ui/widgetabout.h>
#include "ui_widgetabout.h"

#include <application.h>

WidgetAbout::WidgetAbout(ApplicationGui *_applicationGui, const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent) :
    Widget(_applicationGui, _guiScale, _guiFontXL, _guiFontL, _guiFontM, _guiFontS, _parent),
    ui(new Ui::WidgetAbout) {
    ui->setupUi(this);
}

WidgetAbout::~WidgetAbout() {
    delete ui;
}

void WidgetAbout::update() {
    Widget::update();
}

void WidgetAbout::initializeGui() {
    Widget::initializeGui();
    // acquire application
    if(!applicationGui && !applicationGui->getApplication()) return;
    const Application *application = applicationGui->getApplication();
    // initialize GUI elements
    ui->labelTitle->setFont(guiFontXL);
    ui->labelApplicationName->setFont(guiFontL);
    ui->labelApplicationCopyright->setFont(guiFontM);
    ui->labelProjectInformation->setFont(guiFontM);
    // initialize GUI elements
    ui->labelApplicationName->setText(QString("%1 %2").arg(application->getApplicationName()).arg(application->getApplicationVersion()));
    ui->labelApplicationCopyright->setText(QString("%1").arg(application->getApplicationCopyright()));
}
