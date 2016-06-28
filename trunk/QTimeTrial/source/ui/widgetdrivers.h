// widgetdrivers.h

#ifndef _WIDGETDRIVERS_H_
#define _WIDGETDRIVERS_H_

#include <main.h>

#include <ui/widget.h>

namespace Ui {
    class WidgetDrivers;
}

class WidgetDrivers : public Widget {
    Q_OBJECT
public:
    WidgetDrivers(QWidget *_parent = 0);
    ~WidgetDrivers();
private:
    Ui::WidgetDrivers *ui;
public slots:
    void update();
private:
    void updateLineEditCurrentDriver();
    void updateListWidgetAvailableDrivers();
private slots:
    void slotDoubleClickedListWidgetAvailableDrivers(QListWidgetItem *_item);
    void slotPressedPushButtonCreateDriver();
    void slotPressedPushButtonSetCurrentDriver();
    void slotPressedPushButtonDeleteDriver();
};

#endif
