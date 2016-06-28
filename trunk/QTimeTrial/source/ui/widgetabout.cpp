// widgetabout.cpp

#include <ui/widgetabout.h>
#include "ui_widgetabout.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

WidgetAbout::WidgetAbout(QWidget *parent) :
    Widget(parent),
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
