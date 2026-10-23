#include "scheduleitem.h"
#include "applicationlist.h"
#include "ui_scheduleitem.h"

ScheduleItem::ScheduleItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScheduleItem)
{
    ui->setupUi(this);

    connect(ui->editScheduleButton, &QPushButton::clicked, 
        this, [this]() {emit editRequested(schedule, applicationLists);});

    connect(ui->deleteScheduleButton, &QPushButton::clicked, 
        this, [this]() {emit deleteRequested(schedule.id, schedule.name);});
}

ScheduleItem::~ScheduleItem()
{
    delete ui;
}

void ScheduleItem::setSchedule(const sun::persistence::Schedule& schedule, const QList<sun::persistence::ApplicationList>& applicationLists)
{
    this->schedule = schedule;
    this->applicationLists = applicationLists;

    ui->scheduleName->setText(schedule.name);
    ui->applicationList->setApplicationList(applicationLists);

    QString status;

    if (schedule.type == sun::persistence::Schedule::TimeWindow) {
        status = QString("Active from %1 to %2").arg(schedule.startsAt->toString("HH:mm"), schedule.endsAt->toString("HH:mm"));
    } else if (schedule.type == sun::persistence::Schedule::DailyLimit) {
        status = QString("%1h per day").arg(*schedule.dailyLimit / 3600);
    }
    ui->scheduleStatus->setText(status);
}
