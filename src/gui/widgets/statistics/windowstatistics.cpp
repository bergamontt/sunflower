#include "windowstatistics.h"
#include "ui_windowstatistics.h"

#include <QIcon>
#include <QStyle>

WindowStatistics::WindowStatistics(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WindowStatistics)
{
    ui->setupUi(this);
    setProgramIcon(QIcon(":gui/exe-file.svg"));
}

WindowStatistics::~WindowStatistics()
{
    delete ui;
}

QString WindowStatistics::getProgramName() const
{
    return programName;
}

void WindowStatistics::setProgramName(const QString& name)
{
    programName = name;
    ui->programLabel->setText(name);
}

QIcon WindowStatistics::getProgramIcon() const
{
    return programIcon;
}

void WindowStatistics::setProgramIcon(const QIcon& icon)
{
    if(!icon.isNull())
    {
        programIcon = icon;
        ui->programIcon->setPixmap(icon.pixmap(24, 24));
    }
}

QString WindowStatistics::getWorkTime() const
{
    return workTime;
}

void WindowStatistics::setWorkTime(const QString& time)
{
    workTime = time;
    ui->workTimeLabel->setText(time);
}

QString WindowStatistics::getWorkTimeIconPath() const
{
    return workTimeIconPath;
}

void WindowStatistics::setWorkTimeIconPath(const QString& path)
{
    workTimeIconPath = path;
    const QIcon icon(path);
    ui->workTimeIcon->setPixmap(icon.isNull() ? QPixmap{} : icon.pixmap(24, 24));
}

QString WindowStatistics::getTimeLeft() const
{
    return timeLeft;
}

void WindowStatistics::setTimeLeft(const QString& time)
{
    timeLeft = time;
    ui->timeLeft->setText(time);
}