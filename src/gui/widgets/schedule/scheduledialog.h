#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H

#include "applicationlist.h"
#include "schedule.h"
#include <QDialog>

namespace Ui {
class ScheduleDialog;
}

class ScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScheduleDialog(QWidget *parent = nullptr);
    ~ScheduleDialog();

    void setSchedule(const sun::persistence::Schedule& schedule, const QList<sun::persistence::ApplicationList>& applicationLists);
    sun::persistence::CreateScheduleDto getSchedule() const;
    QList<sun::persistence::ApplicationList> getApplicationLists() const;

private slots:
    void onAddApplicationsButtonClicked();

private:
    Ui::ScheduleDialog *ui;
    QList<sun::persistence::ApplicationList> applicationLists;

    void validateForm();

};

#endif // SCHEDULEDIALOG_H
