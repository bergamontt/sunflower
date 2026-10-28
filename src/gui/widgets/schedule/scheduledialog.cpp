#include "scheduledialog.h"
#include "applicationdialog.h"
#include "schedule.h"
#include "ui_scheduledialog.h"
#include <qdialog.h>
#include <qpushbutton.h>

#include <QButtonGroup>
#include <QStyle>

ScheduleDialog::ScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScheduleDialog)
{
    ui->setupUi(this);
    setWindowTitle("Create new Schedule");

    connect(ui->addApplicationsButton, &QPushButton::clicked, this, [this](){
        ApplicationDialog appliactionDialog;
        if(!applicationLists.empty()) {
            appliactionDialog.setSelectedApplicationLists(applicationLists);
        }
        if(appliactionDialog.exec() == QDialog::Accepted) {
            applicationLists = appliactionDialog.getSelectedApplicationLists();
            ui->applicationShortList->setApplicationList(applicationLists);
            validateForm();
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

    connect(ui->scheduleNameEdit,
        &QLineEdit::textChanged,
        this,
        &ScheduleDialog::validateForm);   
    
    connect(ui->blockButton, &QPushButton::clicked, this, [this]() {
            ui->blockTypeContainer->setCurrentIndex(0);
            ui->blockButton->setChecked(true);
            ui->limitButton->setChecked(false);
            validateForm();
        });

    connect(ui->limitButton, &QPushButton::clicked, this, [this]() {
            ui->blockTypeContainer->setCurrentIndex(1);
            ui->blockButton->setChecked(false);
            ui->limitButton->setChecked(true);
            validateForm();
        });

    connect(ui->fromTime, &QTimeEdit::timeChanged, this, [this](const QTime &time) {
            if (ui->toTime->time() <= time) {
                ui->toTime->setTime(time.addSecs(60));
            }
        });

    connect(ui->toTime, &QTimeEdit::timeChanged, this, [this](const QTime &time) {
            if (ui->fromTime->time() >= time) {
                ui->fromTime->setTime(time.addSecs(-60));
            }
        });

    ui->fromTime->setMinimumTime(QTime(0, 0));
    ui->fromTime->setMaximumTime(QTime(23, 58));

    ui->toTime->setMinimumTime(QTime(0, 1));
    ui->toTime->setMaximumTime(QTime(23, 59));

    ui->timeAllowed->setMinimumTime(QTime(0, 1));

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

    for (QWidget *widget : ui->blockTypeContainer->findChildren<QWidget *>()) {
        widget->style()->unpolish(widget);
        widget->style()->polish(widget);
        widget->update();
    }

    resize(435, 463);
}

ScheduleDialog::~ScheduleDialog()
{
    delete ui;
}

void ScheduleDialog::setSchedule(const sun::persistence::Schedule& schedule, const QList<sun::persistence::ApplicationList>& applicationLists) {
    this->applicationLists = applicationLists;
  
    setWindowTitle("Edit \"" + schedule.name + "\" schedule");

    ui->scheduleNameEdit->setText(schedule.name);
    ui->applicationShortList->setApplicationList(applicationLists);

    if(schedule.type == sun::persistence::Schedule::Type::DailyLimit) {
        ui->limitButton->click();
        ui->timeAllowed->setTime(QTime::fromMSecsSinceStartOfDay(*schedule.dailyLimit * 1000));
    } else {
        ui->fromTime->setTime(*schedule.startsAt);
        ui->toTime->setTime(*schedule.endsAt);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::Day::MON) {
        ui->mondayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::Day::TUE) {
        ui->tuesdayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::Day::WED) {
        ui->wednesdayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::Day::THU) {
        ui->thursdayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::Day::FRI) {
        ui->fridayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::Day::SAT) {
        ui->saturdayButton->setChecked(true);
    }

    if (schedule.repeatAt & sun::persistence::Schedule::Day::SUN) {
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
        schedule.repeatAt |= sun::persistence::Schedule::Day::MON;
    }

    if (ui->tuesdayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::Day::TUE;
    }

    if (ui->wednesdayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::Day::WED;
    }

    if (ui->thursdayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::Day::THU;
    }

    if (ui->fridayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::Day::FRI;
    }

    if (ui->saturdayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::Day::SAT;
    }

    if (ui->sundayButton->isChecked()) {
        schedule.repeatAt |= sun::persistence::Schedule::Day::SUN;
    }

    return schedule;
}

QList<sun::persistence::ApplicationList> ScheduleDialog::getApplicationLists() const
{
    return applicationLists;
}

void ScheduleDialog::validateForm()
{
    ui->doneButton->setDisabled(false);

    if(ui->scheduleNameEdit->text().isEmpty()) ui->doneButton->setDisabled(true);
    if(applicationLists.empty()) ui->doneButton->setDisabled(true);
}
