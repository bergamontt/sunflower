#include "schedulepage.h"
#include "applicationlist.h"
#include "schedule.h"
#include "scheduledialog.h"
#include "deletescheduledialog.h"
#include "scheduleitem.h"
#include "ui_schedulepage.h"
#include "scheduledialog.h"
#include <qnamespace.h>

using namespace sun::persistence;

SchedulePage::SchedulePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchedulePage)
{
    ui->setupUi(this);
    ui->scheduleList->setAlignment(Qt::AlignTop);
    loadSchedules();

    connect(ui->newScheduleButton, &QPushButton::clicked,
        this, &SchedulePage::onCreateScheduleButtonClicked);
}

SchedulePage::~SchedulePage()
{
    delete ui;
}

void SchedulePage::loadSchedules()
{ 
    const QList<Schedule> schedules = scheduleService.getAll();
    for (const Schedule& schedule : schedules)
        insertSchedule(schedule);
}

void SchedulePage::insertSchedule(const Schedule& schedule)
{
    ScheduleItem* item = new ScheduleItem(this);
    item->setObjectName("scheduleItem-" + QString::number(schedule.id));

    QList<ApplicationList> applicationlists = scheduleService.getAllApplicationLists(schedule.id);
    item->setSchedule(schedule, applicationlists);

    connect(item, &ScheduleItem::deleteRequested,
        this, &SchedulePage::onDeleteScheduleRequested);

    connect(item, &ScheduleItem::editRequested,
        this, &SchedulePage::onEditScheduleRequested);

    ui->scheduleList->addWidget(item);
}

void SchedulePage::onCreateScheduleButtonClicked()
{
    ScheduleDialog* dialog = new ScheduleDialog(this);
    if(dialog->exec() == QDialog::Accepted)
    {
        CreateScheduleDto scheduleDto = dialog->getSchedule();
        Schedule schedule = scheduleService.create(scheduleDto);

        QList<ApplicationList> applicationLists = dialog->getApplicationLists();
        for(ApplicationList applicationlist : applicationLists)
            scheduleService.addApplicationList(schedule.id, applicationlist.id);

        insertSchedule(schedule);
    }
}

void SchedulePage::onEditScheduleRequested(Schedule schedule, QList<ApplicationList> applicationLists)
{
    ScheduleDialog* scheduleDialog = new ScheduleDialog(this);
    scheduleDialog->setSchedule(schedule, applicationLists);
    
    if(scheduleDialog->exec() == QDialog::Accepted)
    {
        const CreateScheduleDto& createScheduleDto = scheduleDialog->getSchedule();
        UpdateScheduleDto updateScheduleDto;
        updateScheduleDto.id = schedule.id;
        updateScheduleDto.name = createScheduleDto.name;
        updateScheduleDto.type = createScheduleDto.type;
        updateScheduleDto.dailyLimit = createScheduleDto.dailyLimit;
        updateScheduleDto.startsAt = createScheduleDto.startsAt;
        updateScheduleDto.endsAt = createScheduleDto.endsAt;
        updateScheduleDto.repeatAt = createScheduleDto.repeatAt;
        QList<ApplicationList> newApplicationLists = scheduleDialog->getApplicationLists();
        const Schedule& newSchedule = scheduleService.updateById(updateScheduleDto, newApplicationLists);

        ScheduleItem *item = findChild<ScheduleItem*>("scheduleItem-" + QString::number(schedule.id));
        if(item)
            item->setSchedule(newSchedule, newApplicationLists);
    }
}

void SchedulePage::onDeleteScheduleRequested(int scheduleId, QString scheduleName)
{
    DeleteScheduleDialog* deleteDialog = new DeleteScheduleDialog(this);
    deleteDialog->setSchedule(scheduleName);

    if(deleteDialog->exec() == QDialog::Accepted)
    {
        scheduleService.deleteById(scheduleId);
        QWidget *item = findChild<QWidget*>("scheduleItem-" + QString::number(scheduleId));
        if (item)
            item->deleteLater();
    }
}