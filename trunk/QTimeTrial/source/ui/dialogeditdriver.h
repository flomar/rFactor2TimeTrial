// dialogeditdriver.h

#ifndef _DIALOGEDITDRIVER_H_
#define _DIALOGEDITDRIVER_H_

#include <main.h>

#include <ui/dialog.h>

namespace Ui {
    class DialogEditDriver;
}

class DialogEditDriver : public Dialog {
    Q_OBJECT
public:
    DialogEditDriver(const QString &_driverName, const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS);
    virtual ~DialogEditDriver();
private:
    Ui::DialogEditDriver *ui;
public slots:
    virtual void update();
protected:
    virtual void initializeGui();
private slots:
    void slotPressedPushButtonOK();
    void slotPressedPushButtonCancel();
private:
    const QString driverName;
};

#endif
