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

    bool operator<(const ScheduleItem& other) const
    {
        if(schedule.isActive != other.schedule.isActive)
            return schedule.isActive < other.schedule.isActive;
        return schedule.name < other.schedule.name;
    }

private:
    Ui::ScheduleItem *ui;
    sun::persistence::Schedule schedule;
    QList<sun::persistence::ApplicationList> applicationLists;

signals:
    void editRequested(const sun::persistence::Schedule& schedule, const QList<sun::persistence::ApplicationList>& applicationLists);
    void deleteRequested(int scheduleId, QString scheduleName);
    void isActiveChangeRequested(int scheduleId, bool isActive);
};

#endif // SCHEDULEITEM_H
