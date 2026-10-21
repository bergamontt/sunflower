#include "scheduleitem.h"
#include "ui_scheduleitem.h"

ScheduleItem::ScheduleItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScheduleItem)
{
    ui->setupUi(this);
}

ScheduleItem::~ScheduleItem()
{
    delete ui;
}