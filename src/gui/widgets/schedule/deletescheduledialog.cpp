#include "deletescheduledialog.h"
#include "ui_deletescheduledialog.h"

DeleteScheduleDialog::DeleteScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteScheduleDialog)
{
    ui->setupUi(this);
}

DeleteScheduleDialog::~DeleteScheduleDialog()
{
    delete ui;
}

void DeleteScheduleDialog::setSchedule(QString scheduleName) {
    ui->dialogText->setText("Are you sure you wish to delete " + scheduleName + " schedule?");
}