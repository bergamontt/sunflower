#include "passwordconfirmation.h"
#include "ui_passwordconfirmation.h"

#include "password/passwordservice.h"
#include "settings/settingsservice.h"

#include <QMessageBox>

PasswordConfirmation::PasswordConfirmation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordConfirmation),
    passwordService(std::make_unique<sun::core::PasswordService>()),
    settingService(std::make_unique<sun::core::SettingsService>())
{
    ui->setupUi(this);
    connect(ui->confirmButton, &QPushButton::clicked, this, &PasswordConfirmation::onConfirm);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

PasswordConfirmation::~PasswordConfirmation()
{
    delete ui;
}

bool PasswordConfirmation::confirm(QWidget *parent)
{
    static sun::core::SettingsService settings;
    if (settings.lockPolicy().lockType() != sun::core::LockType::Password)
    {
        return true;
    }
    PasswordConfirmation dialog(parent);
    return dialog.exec() == QDialog::Accepted;
}

void PasswordConfirmation::onConfirm()
{
    const QString savedHash = settingService->lockPolicy().hash();
    const QString enteredHash = passwordService->hash(ui->passwordLineEdit->text());
    if (passwordService->matchPasswords(enteredHash, savedHash))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Wrong password");
        ui->passwordLineEdit->clear();
    }
}
