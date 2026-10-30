#include "schedulepage.h"
#include "applicationlist.h"
#include "schedule.h"
#include "schedule/scheduleservice.h"
#include "scheduledialog.h"
#include "deletedialog.h"
#include "scheduleitem.h"
#include "ui_schedulepage.h"
#include "scheduledialog.h"
#include <qnamespace.h>

using namespace sun::persistence;
using namespace sun::core;

SchedulePage::SchedulePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchedulePage),
    scheduleService(std::make_unique<ScheduleService>())
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
    const QList<Schedule> schedules = scheduleService->getAll();
    for (const Schedule& schedule : schedules)
        insertSchedule(schedule);
    sortSchedules();
}

void SchedulePage::insertSchedule(const Schedule& schedule)
{
    ScheduleItem* item = new ScheduleItem(this);
    item->setObjectName("scheduleItem-" + QString::number(schedule.id));
    item->setProperty("scheduleName", schedule.name);

    QList<ApplicationList> applicationlists = scheduleService->getAllApplicationLists(schedule.id);
    item->setSchedule(schedule, applicationlists);

    connect(item, &ScheduleItem::deleteRequested,
        this, &SchedulePage::onDeleteScheduleRequested);

    connect(item, &ScheduleItem::editRequested,
        this, &SchedulePage::onEditScheduleRequested);

    connect(item, &ScheduleItem::isActiveChangeRequested,
        this, &SchedulePage::onIsActiveChangeRequested);

    ui->scheduleList->addWidget(item);
}

void SchedulePage::onCreateScheduleButtonClicked()
{
    ScheduleDialog* dialog = new ScheduleDialog(this);
    if(dialog->exec() == QDialog::Accepted)
    {
        CreateScheduleDto scheduleDto = dialog->getSchedule();
        Schedule schedule = scheduleService->create(scheduleDto);

        QList<ApplicationList> applicationLists = dialog->getApplicationLists();
        for(ApplicationList applicationlist : applicationLists)
            scheduleService->addApplicationList(schedule.id, applicationlist.id);

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
        const Schedule& newSchedule = scheduleService->updateById(updateScheduleDto, newApplicationLists);

        ScheduleItem *item = findChild<ScheduleItem*>("scheduleItem-" + QString::number(schedule.id));
        if(item)
        {
            item->setSchedule(newSchedule, newApplicationLists);
            sortSchedules();
        }
    }
}

void SchedulePage::onDeleteScheduleRequested(int scheduleId, QString scheduleName)
{
    DeleteDialog* deleteDialog = new DeleteDialog(this);
    deleteDialog->setItem(scheduleName);

    if(deleteDialog->exec() == QDialog::Accepted)
    {
        scheduleService->deleteById(scheduleId);
        QWidget *item = findChild<QWidget*>("scheduleItem-" + QString::number(scheduleId));
        if (item)
            item->deleteLater();
    }
}

void SchedulePage::onIsActiveChangeRequested(int scheduleId, bool isActive)
{
    scheduleService->updateIsActiveById(scheduleId, isActive);
    sortSchedules();
}

void SchedulePage::sortSchedules()
{
    QList<ScheduleItem*> scheduleItems;

    while (ui->scheduleList->count() > 0)
    {
        QLayoutItem *item = ui->scheduleList->takeAt(0);

        if (ScheduleItem *scheduleItem = qobject_cast<ScheduleItem*>(item->widget()))
        {
            scheduleItems.append(scheduleItem);
        }

        delete item;
    }

    std::sort(scheduleItems.begin(), scheduleItems.end(),
        [](ScheduleItem *a, ScheduleItem *b)
        {
            return *a < *b;
        });

    for (ScheduleItem *scheduleItem : scheduleItems)
        ui->scheduleList->addWidget(scheduleItem);
}
