#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QWidget>

namespace Ui {
class ScheduleItem;
}

class ScheduleItem : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleItem(QWidget *parent = nullptr);
    ~ScheduleItem();

private:
    Ui::ScheduleItem *ui;
};

#endif // SCHEDULEITEM_H
