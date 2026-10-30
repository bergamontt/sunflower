#ifndef SCHEDULEPAGE_H
#define SCHEDULEPAGE_H

#include <QWidget>

#include <memory>

#include "applicationlist.h"
#include "schedule.h"
#include "schedule/ischeduledservice.h"

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
    void onIsActiveChangeRequested(int scheduleId, bool isActive);
    void onCreateScheduleButtonClicked();

private:
    Ui::SchedulePage *ui;
    std::unique_ptr<sun::core::IScheduleService> scheduleService;
    void loadSchedules();
    void insertSchedule(const sun::persistence::Schedule& schedule);
    void sortSchedules();
};

#endif // SCHEDULEPAGE_H
