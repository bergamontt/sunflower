#include "scheduledialog.h"
#include "applicationdialog.h"
#include "schedule.h"
#include "ui_scheduledialog.h"
#include <qdialog.h>
#include <qpushbutton.h>

ScheduleDialog::ScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScheduleDialog)
{
    ui->setupUi(this);

    connect(ui->addApplicationsButton, &QPushButton::clicked, this, [this](){
        ApplicationDialog appliactionDialog;
        if(!applicationLists.empty()) {
            appliactionDialog.setApplicationLists(applicationLists);
        }
        if(appliactionDialog.exec() == QDialog::Accepted) {
            applicationLists = appliactionDialog.getSelectedApplicationListsIds();
            ui->applicationShortList->setApplicationList(applicationLists);
        }
    });

    connect(
        ui->doneButton,
        &QPushButton::clicked,
        this,
        &QDialog::accept);

    connect(ui->cancelButton, 
        &QPushButton::clicked,
        this,
        &QDialog::reject);
    
    connect(ui->blockButton, &QPushButton::clicked, this, [this]() {
            ui->blockTypeContainer->setCurrentIndex(0);
            ui->blockButton->setChecked(true);
            ui->limitButton->setChecked(false);
        });

    connect(ui->limitButton, &QPushButton::clicked, this, [this]() {
                ui->blockTypeContainer->setCurrentIndex(1);
                ui->blockButton->setChecked(false);
                ui->limitButton->setChecked(true);
            });

    connect(ui->fromTime, &QTimeEdit::timeChanged, this, [this](const QTime &time) {
        if (ui->toTime->time() < time) {
            ui->toTime->setTime(time);
        }
    });

    connect(ui->toTime, &QTimeEdit::timeChanged, this, [this](const QTime &time) {
        if (ui->fromTime->time() > time) {
            ui->fromTime->setTime(time);
        }
    });

    QPushButton *buttons[] = {
        ui->mondayButton,
        ui->tuesdayButton,
        ui->wednesdayButton,
        ui->thursdayButton,
        ui->fridayButton,
        ui->saturdayButton,
        ui->sundayButton
    };

    for (QPushButton *button : buttons) {
        connect(button, &QPushButton::clicked,
                this, [this, button, buttons]() {
            if (!button->isChecked()) {
                int numChecked = 0;

                for(QPushButton *butt : buttons) {
                    if (butt->isChecked()) ++numChecked;
                }

                if(numChecked == 0)button->setChecked(true);
            }
        });
    }
}

ScheduleDialog::~ScheduleDialog()
{
    delete ui;
}

void ScheduleDialog::setSchedule(const sun::persistence::Schedule& schedule, const QList<sun::persistence::ApplicationList>& applicationLists) {
    this->applicationLists = applicationLists;

    ui->scheduleNameEdit->setText(schedule.name);
    ui->applicationShortList->setApplicationList(applicationLists);

    if(schedule.type == sun::persistence::Schedule::Type::DailyLimit) {
        ui->limitButton->click();
        ui->timeAllowed->setTime(QTime::fromMSecsSinceStartOfDay(*schedule.dailyLimit * 1000));
    } else {
        ui->fromTime->setTime(*schedule.startsAt);
        ui->toTime->setTime(*schedule.endsAt);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::WeekDay::MON) {
        ui->mondayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::WeekDay::TUE) {
        ui->tuesdayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::WeekDay::WED) {
        ui->wednesdayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::WeekDay::THU) {
        ui->thursdayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::WeekDay::FRI) {
        ui->fridayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::WeekDay::SAT) {
        ui->saturdayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::WeekDay::SUN) {
        ui->sundayButton->setChecked(true);
    }
};

sun::persistence::CreateScheduleDto ScheduleDialog::getSchedule() const
{
    sun::persistence::CreateScheduleDto schedule;

    schedule.name = ui->scheduleNameEdit->text();

    if (ui->limitButton->isChecked()) {
        schedule.type = sun::persistence::Schedule::Type::DailyLimit;
        schedule.dailyLimit = ui->timeAllowed->time().msecsSinceStartOfDay() / 1000;
    } else {
        schedule.type = sun::persistence::Schedule::Type::TimeWindow;
        schedule.startsAt = ui->fromTime->time();
        schedule.endsAt = ui->toTime->time();
    }

    schedule.repeatAt = 0;

    if (ui->mondayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::WeekDay::MON;
    }

    if (ui->tuesdayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::WeekDay::TUE;
    }

    if (ui->wednesdayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::WeekDay::WED;
    }

    if (ui->thursdayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::WeekDay::THU;
    }

    if (ui->fridayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::WeekDay::FRI;
    }

    if (ui->saturdayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::WeekDay::SAT;
    }

    if (ui->sundayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::WeekDay::SUN;
    }

    return schedule;
}

QList<sun::persistence::ApplicationList> ScheduleDialog::getApplicationLists() const
{
    return applicationLists;
}

