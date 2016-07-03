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
    DialogDeleteDriver(const QString &_driverName, const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS);
    virtual ~DialogDeleteDriver();
private:
    Ui::DialogDeleteDriver *ui;
public slots:
    virtual void update();
protected:
    virtual void initializeGui();
private slots:
    void slotPressedPushButtonOK();
    void slotPressedPushButtonCancel();
private:
    const QString driverName;
public:
    QString getDriverName() const;
};

#endif
