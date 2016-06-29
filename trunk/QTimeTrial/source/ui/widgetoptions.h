// widgetoptions.h

#ifndef _WIDGETOPTIONS_H_
#define _WIDGETOPTIONS_H_

#include <main.h>

#include <ui/widget.h>

namespace Ui {
    class WidgetOptions;
}

class WidgetOptions : public Widget {
    Q_OBJECT
public:
    WidgetOptions(QWidget *_parent = 0);
    ~WidgetOptions();
private:
    Ui::WidgetOptions *ui;
public slots:
    void update();
private:
    void updateCheckBoxes();
private slots:
    void slotToggledCheckBoxAutoDeleteSessions(const bool _checked);
    void slotToggledCheckBoxAutoDeleteRuns(const bool _checked);
    void slotToggledCheckBoxAutoDeleteLaps(const bool _checked);
};

#endif
