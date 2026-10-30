#include "scheduleitem.h"
#include "applicationlist.h"
#include "ui_scheduleitem.h"
#include <qabstractitemview.h>
#include <qstyle.h>

using namespace sun::persistence;

ScheduleItem::ScheduleItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScheduleItem)
{
    ui->setupUi(this);

    connect(ui->editScheduleButton, &QPushButton::clicked, 
        this, [this]() {emit editRequested(schedule, applicationLists);});

    connect(ui->deleteScheduleButton, &QPushButton::clicked, 
        this, [this]() {emit deleteRequested(schedule.id, schedule.name);});

    connect(ui->onButton, &QPushButton::clicked,
        this, &ScheduleItem::onIsActiveStatusChanged);
}

ScheduleItem::~ScheduleItem()
{
    delete ui;
}

void ScheduleItem::setSchedule(const Schedule& schedule, const QList<ApplicationList>& applicationLists)
{
    this->schedule = schedule;
    this->applicationLists = applicationLists;

    ui->scheduleName->setText(schedule.name);
    ui->applicationList->setApplicationLists(applicationLists);

    QString status;

    if (schedule.type == Schedule::TimeWindow)
        status = QString("Active from %1 to %2").arg(schedule.startsAt->toString("HH:mm"), schedule.endsAt->toString("HH:mm"));
    else if (schedule.type == Schedule::DailyLimit)
    {
        const int totalMinutes = *schedule.dailyLimit / 60;
        const int hours = totalMinutes / 60;
        const int minutes = totalMinutes % 60;

        QString duration;

        if (hours > 0)
            duration += QString("%1h").arg(hours);

        if (minutes > 0) {
            if (!duration.isEmpty())
                duration += " ";

            duration += QString("%1m").arg(minutes);
        }

        status = QString("%1 per day").arg(duration);
    }
    ui->scheduleStatus->setText(status);
    if(!schedule.isActive)
        ui->onButton->setChecked(false);
}

void ScheduleItem::onIsActiveStatusChanged()
{
    schedule.isActive = ui->onButton->isChecked();
    setProperty("scheduleItemClass", schedule.isActive ? "isActive" : "isNotActive");
    style()->unpolish(this);
    style()->polish(this);

    for (auto *child : findChildren<QWidget*>()) {
        child->style()->unpolish(child);
        child->style()->polish(child);
        child->update();
    }

    update();
    emit isActiveChangeRequested(schedule.id, ui->onButton->isChecked());
}
