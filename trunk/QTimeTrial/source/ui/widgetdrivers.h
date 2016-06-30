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
    WidgetDrivers(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent = 0);
    ~WidgetDrivers();
private:
    Ui::WidgetDrivers *ui;
public slots:
    void update();
protected:
    virtual void initializeGui();
private:
    void updateLineEditCurrentDriver();
    void updateListWidgetAvailableDrivers();
private slots:
    void slotDoubleClickedListWidgetAvailableDrivers(QListWidgetItem *_item);
    void slotPressedPushButtonCreateDriver();
    void slotPressedPushButtonEditDriver();
    void slotPressedPushButtonDeleteDriver();
};

#endif
