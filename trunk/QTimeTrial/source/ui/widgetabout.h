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
    WidgetAbout(QWidget *_parent = 0);
    ~WidgetAbout();
private:
    Ui::WidgetAbout *ui;
public slots:
    void update();
};

#endif
