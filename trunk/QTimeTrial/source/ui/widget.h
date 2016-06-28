// widget.h

#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <main.h>

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *_parent = 0);
    virtual ~Widget();
public slots:
    virtual void update();
protected:
    const QColor colorWidgetBackground;
    const QColor colorWidgetBorder;
    const QColor colorButtonBackground;
    const QColor colorButtonBackgroundHovered;
    const QColor colorButtonBorder;
    const QColor colorButtonBorderHovered;
    const QColor colorButtonText;
    const QColor colorButtonTextHovered;
};

#endif
