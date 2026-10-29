#include "scheduledialog.h"
#include "applicationdialog.h"
#include "applicationlist.h"
#include "schedule.h"
#include "ui_scheduledialog.h"
#include <qdialog.h>
#include <qpushbutton.h>

#include <QButtonGroup>
#include <QStyle>

using namespace sun::persistence;

ScheduleDialog::ScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScheduleDialog)
{
    ui->setupUi(this);
    setWindowTitle("Create new Schedule");

    connect(ui->doneButton, &QPushButton::clicked,
        this, &QDialog::accept);

    connect(ui->cancelButton, &QPushButton::clicked,
        this, &QDialog::reject);

    connect(ui->scheduleNameEdit, &QLineEdit::textChanged,
        this, &ScheduleDialog::validateForm);   

    connect(ui->addApplicationsButton, &QPushButton::clicked,
        this, &ScheduleDialog::onAddApplicationsButtonClicked);
    
    connect(ui->blockButton, &QPushButton::clicked, this, [this]() 
        {
            ui->blockTypeContainer->setCurrentIndex(0);
            ui->blockButton->setChecked(true);
            ui->limitButton->setChecked(false);
        });

    connect(ui->limitButton, &QPushButton::clicked, this, [this]() 
        {
            ui->blockTypeContainer->setCurrentIndex(1);
            ui->blockButton->setChecked(false);
            ui->limitButton->setChecked(true);
        });

    connect(ui->fromTime, &QTimeEdit::timeChanged, this, [this](const QTime &time) 
        {
            if (ui->toTime->time() <= time)
                ui->toTime->setTime(time.addSecs(60));
        });

    connect(ui->toTime, &QTimeEdit::timeChanged, this, [this](const QTime &time) 
        {
            if (ui->fromTime->time() >= time)
                ui->fromTime->setTime(time.addSecs(-60));
        });

    ui->blockTypeContainer->setCurrentIndex(0);

    ui->fromTime->setTimeRange(QTime(0, 0), QTime(23, 58));
    ui->toTime->setTimeRange(QTime(0, 1), QTime(23, 59));
    ui->timeAllowed->setTimeRange(QTime(0, 1), QTime(23, 59));

    QPushButton *buttons[] =
    {
        ui->mondayButton,
        ui->tuesdayButton,
        ui->wednesdayButton,
        ui->thursdayButton,
        ui->fridayButton,
        ui->saturdayButton,
        ui->sundayButton
    };

    for (QPushButton *button : buttons)
    {
        connect(button, &QPushButton::clicked,
                this, [this, button, buttons]() 
            {
                if (!button->isChecked())
                {
                    int numChecked = 0;

                    for(QPushButton *butt : buttons)
                        if (butt->isChecked()) ++numChecked;

                    if(numChecked == 0)
                        button->setChecked(true);
                }
            });
    }

    for (QWidget *widget : ui->blockTypeContainer->findChildren<QWidget*>()) {
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

void ScheduleDialog::onAddApplicationsButtonClicked()
{
    ApplicationDialog* appliactionDialog = new ApplicationDialog(this);
    if(!applicationLists.empty())
    {
        appliactionDialog->setSelectedApplicationLists(applicationLists);
    }
    if(appliactionDialog->exec() == QDialog::Accepted)
    {
        applicationLists = appliactionDialog->getSelectedApplicationLists();
        ui->applicationShortList->setApplicationLists(applicationLists);
        validateForm();
    }
}

void ScheduleDialog::setSchedule(const Schedule& schedule, const QList<ApplicationList>& applicationLists) {
    setWindowTitle("Edit \"" + schedule.name + "\" schedule");
    ui->scheduleNameEdit->setText(schedule.name);

    this->applicationLists = applicationLists;
    ui->applicationShortList->setApplicationLists(applicationLists);

    if(schedule.type == Schedule::Type::DailyLimit)
    {
        ui->limitButton->click();
        ui->timeAllowed->setTime(QTime::fromMSecsSinceStartOfDay(*schedule.dailyLimit * 1000));
    }
    else
    {
        ui->fromTime->setTime(*schedule.startsAt);
        ui->toTime->setTime(*schedule.endsAt);
    }

    ui->mondayButton->setChecked(schedule.repeatAt & Schedule::Day::MON);
    ui->tuesdayButton->setChecked(schedule.repeatAt & Schedule::Day::TUE);
    ui->wednesdayButton->setChecked(schedule.repeatAt & Schedule::Day::WED);
    ui->thursdayButton->setChecked(schedule.repeatAt & Schedule::Day::THU);
    ui->fridayButton->setChecked(schedule.repeatAt & Schedule::Day::FRI);
    ui->saturdayButton->setChecked(schedule.repeatAt & Schedule::Day::SAT);
    ui->sundayButton->setChecked(schedule.repeatAt & Schedule::Day::SUN);
    validateForm();
};

CreateScheduleDto ScheduleDialog::getSchedule() const
{
    CreateScheduleDto schedule;
    schedule.name = ui->scheduleNameEdit->text();

    if (ui->limitButton->isChecked())
    {
        schedule.type = Schedule::Type::DailyLimit;
        schedule.dailyLimit = ui->timeAllowed->time().msecsSinceStartOfDay() / 1000;
    }
    else
    {
        schedule.type = Schedule::Type::TimeWindow;
        schedule.startsAt = ui->fromTime->time();
        schedule.endsAt = ui->toTime->time();
    }

    schedule.repeatAt = 0;
    if (ui->mondayButton->isChecked())
        schedule.repeatAt |= Schedule::Day::MON;

    if (ui->tuesdayButton->isChecked())
        schedule.repeatAt |= Schedule::Day::TUE;

    if (ui->wednesdayButton->isChecked())
        schedule.repeatAt |= Schedule::Day::WED;

    if (ui->thursdayButton->isChecked())
        schedule.repeatAt |= Schedule::Day::THU;

    if (ui->fridayButton->isChecked())
        schedule.repeatAt |= Schedule::Day::FRI;

    if (ui->saturdayButton->isChecked())
        schedule.repeatAt |= Schedule::Day::SAT;

    if (ui->sundayButton->isChecked())
        schedule.repeatAt |= Schedule::Day::SUN;

    return schedule;
}

QList<ApplicationList> ScheduleDialog::getApplicationLists() const
{
    return applicationLists;
}

void ScheduleDialog::validateForm()
{
    ui->doneButton->setDisabled(false);

    if(ui->scheduleNameEdit->text().isEmpty())
        ui->doneButton->setDisabled(true);
    
    if(applicationLists.empty())
        ui->doneButton->setDisabled(true);
    else
        ui->addApplicationsButton->setIcon(QIcon(":/gui/edit.svg"));
}
