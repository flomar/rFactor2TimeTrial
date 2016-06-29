// dialog.h

#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <main.h>

#include <ui/uiitem.h>

class Dialog : public QDialog, public UiItem {
    Q_OBJECT
public:
    Dialog(QWidget *_parent = 0);
    virtual ~Dialog();
public slots:
    virtual void update();
};

#endif
