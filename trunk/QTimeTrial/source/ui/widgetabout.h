// widgetabout.h

#ifndef _WIDGETABOUT_H_
#define _WIDGETABOUT_H_

#include <main.h>

#include <ui/widget.h>

namespace Ui {
    class WidgetAbout;
}

class WidgetAbout : public Widget {
    Q_OBJECT
public:
    WidgetAbout(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent = 0);
    ~WidgetAbout();
private:
    Ui::WidgetAbout *ui;
public slots:
    void update();
protected:
    virtual void initializeGui();
};

#endif
