// widget.h

#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <main.h>

#include <ui/uiitem.h>

class ApplicationGui;
class ApplicationDatabase;

class Widget : public QWidget, public UiItem {
    Q_OBJECT
public:
    Widget(ApplicationGui *_applicationGui, const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent = 0);
    virtual ~Widget();
protected:
    ApplicationGui *applicationGui;
protected:
    ApplicationDatabase *getApplicationDatabase();
public slots:
    virtual void update();
protected:
    virtual void initializeGui();
protected:
    const float guiScale;
    const QFont guiFontXL;
    const QFont guiFontL;
    const QFont guiFontM;
    const QFont guiFontS;
};

#endif
