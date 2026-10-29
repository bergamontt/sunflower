#include "deletedialog.h"
#include "ui_deletedialog.h"

DeleteDialog::DeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
    setWindowTitle("Delete Confirmation");

    connect(ui->deleteButton, &QPushButton::clicked,
        this, &QDialog::accept);

    connect(ui->cancelButton, &QPushButton::clicked,
        this, &QDialog::reject);
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::setItem(QString name) {
    ui->dialogText->setText("Are you sure you wish to delete " + name + "?");
}