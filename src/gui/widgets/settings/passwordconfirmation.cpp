#include "passwordconfirmation.h"
#include "ui_passwordconfirmation.h"

PasswordConfirmation::PasswordConfirmation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordConfirmation)
{
    ui->setupUi(this);
}

PasswordConfirmation::~PasswordConfirmation()
{
    delete ui;
}
