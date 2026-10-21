#include "applicationdialog.h"
#include "ui_applicationdialog.h"

ApplicationDialog::ApplicationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationDialog)
{
    ui->setupUi(this);
}

ApplicationDialog::~ApplicationDialog()
{
    delete ui;
}
