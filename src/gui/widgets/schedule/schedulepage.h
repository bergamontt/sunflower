#ifndef SCHEDULEPAGE_H
#define SCHEDULEPAGE_H

#include <QWidget>
#include "applicationlist.h"
#include "schedule.h"
#include "schedule/scheduleservice.h"

namespace Ui {
class SchedulePage;
}

class SchedulePage : public QWidget
{
    Q_OBJECT

public:
    explicit SchedulePage(QWidget *parent = nullptr);
    ~SchedulePage();

private slots:
    void onEditScheduleRequested(sun::persistence::Schedule schedule, QList<sun::persistence::ApplicationList> applicationlists);
    void onDeleteScheduleRequested(int scheduleId, QString scheduleName);
    void onCreateScheduleButtonClicked();

private:
    Ui::SchedulePage *ui;
    sun::core::ScheduleService scheduleService;
    void loadSchedules();
    void insertSchedule(const sun::persistence::Schedule& schedule);
};

#endif // SCHEDULEPAGE_H
