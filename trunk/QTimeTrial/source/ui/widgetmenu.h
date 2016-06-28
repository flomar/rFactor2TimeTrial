// widgetmenu.h

#ifndef _WIDGETMENU_H_
#define _WIDGETMENU_H_

#include <main.h>

#include <ui/widget.h>

struct Button {
    Button() : rect(QRect()), text(QString()), hovered(false) { }
    QRect rect;
    QString text;
    bool hovered;
    QPixmap pixmap;
    QPixmap pixmapHovered;
};

class WidgetMenu : public Widget {
    Q_OBJECT
public:
    WidgetMenu(QWidget *_parent = 0);
    virtual ~WidgetMenu();
public slots:
    virtual void update();
signals:
    void signalPressedButtonAbout(const Qt::MouseButton _mouseButton);
    void signalPressedButtonRecords(const Qt::MouseButton _mouseButton);
    void signalPressedButtonDrivers(const Qt::MouseButton _mouseButton);
    void signalPressedButtonOptions(const Qt::MouseButton _mouseButton);
    void signalPressedButtonQuit(const Qt::MouseButton _mouseButton);
protected:
    virtual void enterEvent(QEvent *_event);
    virtual void leaveEvent(QEvent *_event);
    virtual void mouseMoveEvent(QMouseEvent *_event);
    virtual void mousePressEvent(QMouseEvent *_event);
protected:
    virtual void paintEvent(QPaintEvent *_event);
private:
    virtual void updateButtons();
    virtual void deleteButtons();
private:
    bool isButtonHovered(const Button *_button, const QPoint &_point) const;
private:
    QVector<Button*> vectorButtons;
};

#endif
