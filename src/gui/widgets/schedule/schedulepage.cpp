#include "schedulepage.h"
#include "applicationlist.h"
#include "schedule.h"
#include "scheduledialog.h"
#include "deletescheduledialog.h"
#include "scheduleitem.h"
#include "ui_schedulepage.h"
#include "scheduledialog.h"
#include <qnamespace.h>

SchedulePage::SchedulePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchedulePage)
{
    ui->setupUi(this);
    ui->scheduleList->setAlignment(Qt::AlignTop);
    loadSchedules();

    connect(
        ui->newScheduleButton,
        &QPushButton::clicked,
        this,
        &SchedulePage::onCreateScheduleButtonClicked
    );
}

SchedulePage::~SchedulePage()
{
    delete ui;
}

void SchedulePage::loadSchedules()
{ 
    const QList<sun::persistence::Schedule> schedules = scheduleService.getAll();
    for (const sun::persistence::Schedule& schedule : schedules) {
        ScheduleItem* item = new ScheduleItem(this);
        item->setObjectName("scheduleItem-" + QString::number(schedule.id));

        QList<sun::persistence::ApplicationList> applicationlists = scheduleService.getAllApplicationLists(schedule.id);
        item->setSchedule(schedule, applicationlists);

        connect(item, &ScheduleItem::deleteRequested, this, &SchedulePage::onDeleteScheduleRequested);
        connect(item, &ScheduleItem::editRequested, this, &SchedulePage::onEditScheduleRequested);

        ui->scheduleList->addWidget(item);
    }
}

void SchedulePage::onCreateScheduleButtonClicked()
{
    ScheduleDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted) {
        sun::persistence::CreateScheduleDto scheduleDto = dialog.getSchedule();
        sun::persistence::Schedule schedule = scheduleService.create(scheduleDto);
        QList<sun::persistence::ApplicationList> applicationLists = dialog.getApplicationLists();
        for(sun::persistence::ApplicationList applicationlist : applicationLists) {
            scheduleService.addApplicationList(schedule.id, applicationlist.id);
        }
        ScheduleItem* item = new ScheduleItem(this);
        item->setObjectName("scheduleItem-" + QString::number(schedule.id));
        item->setSchedule(schedule, applicationLists);
        connect(item, &ScheduleItem::deleteRequested, this, &SchedulePage::onDeleteScheduleRequested);
        connect(item, &ScheduleItem::editRequested, this, &SchedulePage::onEditScheduleRequested);
        ui->scheduleList->addWidget(item);
    }
}

void SchedulePage::onEditScheduleRequested(sun::persistence::Schedule schedule, QList<sun::persistence::ApplicationList> applicationLists)
{
    ScheduleDialog scheduleDialog;
    scheduleDialog.setSchedule(schedule, applicationLists);
    
    if(scheduleDialog.exec() == QDialog::Accepted) {
        sun::persistence::CreateScheduleDto createScheduleDto = scheduleDialog.getSchedule();

        sun::persistence::UpdateScheduleDto updateScheduleDto;
        updateScheduleDto.id = schedule.id;
        updateScheduleDto.name = createScheduleDto.name;
        updateScheduleDto.type = createScheduleDto.type;
        updateScheduleDto.dailyLimit = createScheduleDto.dailyLimit;
        updateScheduleDto.startsAt = createScheduleDto.startsAt;
        updateScheduleDto.endsAt = createScheduleDto.endsAt;
        updateScheduleDto.repeatAt = createScheduleDto.repeatAt;

        sun::persistence::Schedule newSchedule = scheduleService.updateById(updateScheduleDto);
        QList<sun::persistence::ApplicationList> newApplicationLists = scheduleDialog.getApplicationLists();

        for (const sun::persistence::ApplicationList applicationList : applicationLists) {
            bool shouldKeep = false;

            for (const sun::persistence::ApplicationList& newApplicationList : newApplicationLists) {
                if (applicationList.id == newApplicationList.id) {
                    shouldKeep = true;
                    break;
                }
            }

            if (!shouldKeep) {
                scheduleService.removeApplicationList(schedule.id, applicationList.id);
            }

            for (const sun::persistence::ApplicationList& newApplicationList : newApplicationLists) {
                bool alreadyExists = false;

                for (const sun::persistence::ApplicationList& applicationList : applicationLists) {
                    if (newApplicationList.id == applicationList.id) {
                        alreadyExists = true;
                        break;
                    }
                }

                if (!alreadyExists) {
                    scheduleService.addApplicationList(schedule.id, newApplicationList.id);
                }
            }
        }
        ScheduleItem *item = findChild<ScheduleItem *>("scheduleItem-" + QString::number(schedule.id));
        if (item) item->setSchedule(newSchedule, newApplicationLists);
    }
}

void SchedulePage::onDeleteScheduleRequested(int scheduleId, QString scheduleName)
{
    DeleteScheduleDialog* deleteDialog = new DeleteScheduleDialog(this);
    deleteDialog->setSchedule(scheduleName);

    if(deleteDialog->exec() == QDialog::Accepted) {
        scheduleService.deleteById(scheduleId);
        QWidget *item = findChild<QWidget *>("scheduleItem-" + QString::number(scheduleId));
        if (item) item->deleteLater();
    }
}