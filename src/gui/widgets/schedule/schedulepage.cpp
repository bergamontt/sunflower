#include "schedulepage.h"
#include "ui_schedulepage.h"

SchedulePage::SchedulePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchedulePage)
{
    ui->setupUi(this);
}

SchedulePage::~SchedulePage()
{
    delete ui;
}
