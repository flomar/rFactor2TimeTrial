// dialogdeletedriver.h

#ifndef _DIALOGDELETEDRIVER_H_
#define _DIALOGDELETEDRIVER_H_

#include <main.h>

#include <ui/dialog.h>

namespace Ui {
    class DialogDeleteDriver;
}

class DialogDeleteDriver : public Dialog {
    Q_OBJECT
public:
    DialogDeleteDriver(QWidget *_parent = 0);
    virtual ~DialogDeleteDriver();
private:
    Ui::DialogDeleteDriver *ui;
public slots:
    virtual void update();
private slots:
    void slotPressedPushButtonOK();
    void slotPressedPushButtonCancel();
};

#endif
