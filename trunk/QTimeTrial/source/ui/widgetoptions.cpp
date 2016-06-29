// widgetoptions.cpp

#include <ui/widgetoptions.h>
#include "ui_widgetoptions.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

WidgetOptions::WidgetOptions(QWidget *_parent) :
    Widget(_parent),
    ui(new Ui::WidgetOptions) {
    ui->setupUi(this);
}

WidgetOptions::~WidgetOptions() {
    delete ui;
}

void WidgetOptions::update() {
    Widget::update();
}
