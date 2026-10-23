#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QWidget>
#include "schedule.h"
#include "applicationlist.h"

namespace Ui {
class ScheduleItem;
}

class ScheduleItem : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleItem(QWidget *parent = nullptr);
    ~ScheduleItem();

    void setSchedule(const sun::persistence::Schedule& schedule, const QList<sun::persistence::ApplicationList>& applicationLists);

private:
    Ui::ScheduleItem *ui;
    sun::persistence::Schedule schedule;
    QList<sun::persistence::ApplicationList> applicationLists;

signals:
    void editRequested(const sun::persistence::Schedule& schedule, const QList<sun::persistence::ApplicationList>& applicationLists);
    void deleteRequested(int scheduleId, QString scheduleName);
};

#endif // SCHEDULEITEM_H
