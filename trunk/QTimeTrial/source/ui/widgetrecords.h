// widgetrecords.h

#ifndef _WIDGETRECORDS_H_
#define _WIDGETRECORDS_H_

#include <main.h>

#include <ui/widget.h>

namespace Ui {
    class WidgetRecords;
}

class WidgetRecords : public Widget {
    Q_OBJECT
public:
    WidgetRecords(const float _guiScale, const QFont &_guiFontXL, const QFont &_guiFontL, const QFont &_guiFontM, const QFont &_guiFontS, QWidget *_parent = 0);
    ~WidgetRecords();
private:
    Ui::WidgetRecords *ui;
public slots:
    void update();
protected:
    virtual void initializeGui();
private:
    void updateTableViewAvailableRecords();
    void updateComboBoxes();
private slots:
    void slotChangedCurrentIndexComboBoxLimit(const int _index);
    void slotChangedCurrentIndexComboBoxDriver(const int _index);
    void slotChangedCurrentIndexComboBoxTrack(const int _index);
    void slotChangedCurrentIndexComboBoxCar(const int _index);
    void slotChangedCurrentIndexComboBoxFrontTireCompound(const int _index);
    void slotChangedCurrentIndexComboBoxRearTireCompound(const int _index);
private:
    QVector<Record> calculateVectorRecords() const;
private:
    QVector<Record> vectorRecordsUnsortedAndUnfiltered;
};

#endif
