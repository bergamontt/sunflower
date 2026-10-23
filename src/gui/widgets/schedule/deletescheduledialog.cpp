#include "deletescheduledialog.h"
#include "ui_deletescheduledialog.h"

DeleteScheduleDialog::DeleteScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteScheduleDialog)
{
    ui->setupUi(this);
    setWindowTitle("Schedule deletion confirmation");

    connect(
        ui->deleteButton,
        &QPushButton::clicked,
        this,
        &QDialog::accept);

    connect(ui->cancelButton, 
        &QPushButton::clicked,
        this,
        &QDialog::reject);
}

DeleteScheduleDialog::~DeleteScheduleDialog()
{
    delete ui;
}

void DeleteScheduleDialog::setSchedule(QString scheduleName) {
    ui->dialogText->setText("Are you sure you wish to delete " + scheduleName + " schedule?");
}