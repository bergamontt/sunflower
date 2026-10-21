#include "scheduledialog.h"
#include "ui_scheduledialog.h"

ScheduleDialog::ScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScheduleDialog)
{
    ui->setupUi(this);
    connect(ui->blockButton, &QPushButton::clicked,
        this, [this]() {
            ui->blockTypeContainer->setCurrentIndex(0);
        });

    connect(ui->limitButton, &QPushButton::clicked,
            this, [this]() {
                ui->blockTypeContainer->setCurrentIndex(1);
            });
}

ScheduleDialog::~ScheduleDialog()
{
    delete ui;
}
