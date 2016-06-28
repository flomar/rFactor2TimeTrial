// widgetoptions.cpp

#include <ui/widgetoptions.h>
#include "ui_widgetoptions.h"

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

WidgetOptions::WidgetOptions(QWidget *parent) :
    Widget(parent),
    ui(new Ui::WidgetOptions) {
    ui->setupUi(this);
}

WidgetOptions::~WidgetOptions() {
    delete ui;
}

void WidgetOptions::update() {
    Widget::update();
}
