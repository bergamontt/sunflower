#include "schedulepage.h"
#include "ui_schedulepage.h"
#include "scheduledialog.h"

SchedulePage::SchedulePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchedulePage)
{
    ui->setupUi(this);
    connect(ui->newScheduleButton, &QPushButton::clicked, this, [this]() {
       ScheduleDialog dialog(this);
       dialog.exec();
    });
}

SchedulePage::~SchedulePage()
{
    delete ui;
}
