// dialog.h

#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <main.h>

#include <ui/uiitem.h>

class Dialog : public QDialog, public UiItem {
    Q_OBJECT
public:
    Dialog(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS);
    virtual ~Dialog();
public slots:
    virtual int exec();
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
