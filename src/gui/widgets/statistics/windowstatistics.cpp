#include "windowstatistics.h"
#include "ui_windowstatistics.h"

#include <QIcon>

WindowStatistics::WindowStatistics(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WindowStatistics)
{
    ui->setupUi(this);
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

QString WindowStatistics::getProgramIconPath() const
{
    return programIconPath;
}

void WindowStatistics::setProgramIconPath(const QString& path)
{
    programIconPath = path;
    ui->programIcon->setPixmap(QIcon(path).pixmap(24, 24));
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
    ui->workTimeIcon->setPixmap(QIcon(path).pixmap(24, 24));
}

QString WindowStatistics::getStatus() const
{
    return status;
}

void WindowStatistics::setStatus(const QString& stat)
{
    status = stat;
    ui->status->setText(status);
}