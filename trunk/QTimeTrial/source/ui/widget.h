// widget.h

#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <main.h>

#include <ui/uiitem.h>

class Widget : public QWidget, public UiItem {
    Q_OBJECT
public:
    Widget(QWidget *_parent = 0);
    virtual ~Widget();
public slots:
    virtual void update();
};

#endif
