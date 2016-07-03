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
    DialogCreateDriver(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS);
    virtual ~DialogCreateDriver();
private:
    Ui::DialogCreateDriver *ui;
public slots:
    virtual void update();
protected:
    virtual void initializeGui();
private slots:
    void slotPressedPushButtonOK();
    void slotPressedPushButtonCancel();
public:
    QString getDriverName() const;
};

#endif
