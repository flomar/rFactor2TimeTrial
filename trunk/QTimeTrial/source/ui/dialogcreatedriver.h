// dialogcreatedriver.h

#ifndef _DIALOGCREATEDRIVER_H_
#define _DIALOGCREATEDRIVER_H_

#include <main.h>

#include <ui/dialog.h>

namespace Ui {
    class DialogCreateDriver;
}

class DialogCreateDriver : public Dialog {
    Q_OBJECT
public:
    DialogCreateDriver(QWidget *_parent = 0);
    virtual ~DialogCreateDriver();
private:
    Ui::DialogCreateDriver *ui;
public slots:
    virtual void update();
private slots:
    void slotPressedPushButtonOK();
    void slotPressedPushButtonCancel();
};

#endif
