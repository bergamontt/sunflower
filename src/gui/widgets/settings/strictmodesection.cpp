#include "strictmodesection.h"
#include "password/passwordservice.h"
#include "settings/settingsservice.h"
#include "ui_strictmodesection.h"
#include "passwordconfirmation.h"

#include "strictmodeutils.h"
#include "strictmodetext.h"

#include <QMessageBox>

using namespace sun::gui;
using namespace sun::gui::strict;

using namespace sun::core;

StrictModeSection::StrictModeSection(QWidget *parent) : 
    QFrame(parent),
    ui(new Ui::StrictModeSection),
    settingsService(std::make_unique<SettingsService>()),
    passwordService(std::make_unique<PasswordService>())
{
    ui->setupUi(this);
    
    connect(ui->strictModeComboBox, QOverload<int>::of(&QComboBox::activated),
            this, &StrictModeSection::onLockTypeChanged);
    
    connect(ui->delaySpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &StrictModeSection::onDelayChanged);

    connect(ui->savePasswordButton, &QPushButton::clicked, this, &StrictModeSection::onSaveClicked);
    
    loadCurrentSettings();
}

StrictModeSection::~StrictModeSection()
{
    delete ui;
}

void StrictModeSection::onLockTypeChanged(int index)
{
    if (!PasswordConfirmation::confirm(this))
    {
        QSignalBlocker blocker(ui->strictModeComboBox);
        ui->strictModeComboBox->setCurrentIndex(previousComboIndex);
        return;
    }

    previousComboIndex = index;

    updateSettingsSectionSize(index);
    auto selectedType = indexToLockType(index);
    switch (selectedType)
    {
        case LockType::None:
            settingsService->setLockPolicy(LockPolicy::none());
            break;
        case LockType::Delay:
            settingsService->setLockPolicy(LockPolicy::delay(ui->delaySpinBox->value()));
            break;
        case LockType::Password:
        {
            auto policy = settingsService->lockPolicy();
            updatePasswordSettings(!policy.hash().isEmpty());
            break;
        }
    }
}

void StrictModeSection::onSaveClicked()
{
    auto currentPolicy = settingsService->lockPolicy();
    bool hasPassword = !currentPolicy.hash().isEmpty();

    auto targetPassword = hasPassword 
        ? handleUpdatePassword(currentPolicy.hash()) 
        : handleCreatePassword();
    
    if (!targetPassword.has_value())
    {
        return;
    }

    QString targetHash = passwordService->hash(*targetPassword);
    settingsService->setLockPolicy(LockPolicy::password(targetHash));

    clearPasswordInputs();
    updatePasswordSettings(true);

    QMessageBox::information(this, text::success_window, text::password_saved);
}

void StrictModeSection::onDelayChanged(int seconds) 
{
    if (indexToLockType(ui->strictModeComboBox->currentIndex()) == LockType::Delay)
    {
        settingsService->setLockPolicy(LockPolicy::delay(seconds));
    }
}

void StrictModeSection::updatePasswordSettings(bool hasPassword)
{
    ui->newPasswordLabel->setVisible(hasPassword);
    ui->newPasswordLineEdit->setVisible(hasPassword);

    if (hasPassword)
    {
        ui->repeatPasswordLabel->setText(text::new_password_label);
        ui->repeatPasswordLineEdit->setPlaceholderText(text::new_password_placeholder);
        ui->newPasswordLabel->setText(text::confirm_new_password_label);
    }
    else 
    {
        ui->repeatPasswordLabel->setText(text::confirm_password_label);
        ui->repeatPasswordLineEdit->setPlaceholderText(text::confirm_password_placeholder);
    }
}

void StrictModeSection::loadCurrentSettings()
{
    QSignalBlocker comboBlocker(ui->strictModeComboBox);
    QSignalBlocker spinBlocker(ui->delaySpinBox);
   
    auto policy = settingsService->lockPolicy();
    int targetIndex = lockTypeToIndex(policy.lockType());
    
    previousComboIndex = targetIndex;
    ui->strictModeComboBox->setCurrentIndex(targetIndex);

    bool hasPassword = !policy.hash().isEmpty();
    updatePasswordSettings(hasPassword);
    
    if (policy.lockType() == LockType::Delay)
    {
        ui->delaySpinBox->setValue(policy.delay());
    }
    
    updateSettingsSectionSize(targetIndex);
}

std::optional<QString> StrictModeSection::handleCreatePassword()
{
    QString password = ui->passwordLineEdit->text();
    QString repeatPassword = ui->repeatPasswordLineEdit->text();
    if (!passwordService->matchPasswords(password, repeatPassword))
    {
        QMessageBox::warning(this, text::error_widnow, text::passwords_mismatch);
        return std::nullopt;
    }
    return password;
}

std::optional<QString> StrictModeSection::handleUpdatePassword(const QString& currentHash)
{
    QString currentEnteredPassword = ui->passwordLineEdit->text();
    QString hash = passwordService->hash(currentEnteredPassword);
    if (hash != currentHash)
    {
        QMessageBox::warning(this, text::error_widnow, text::incorrect_current_password);
        return std::nullopt;
    }

    QString newPassword = ui->newPasswordLineEdit->text();
    QString repeatPassword = ui->repeatPasswordLineEdit->text();

    if (!passwordService->matchPasswords(newPassword, repeatPassword))
    {
        QMessageBox::warning(this, text::error_widnow, text::passwords_mismatch);
        return std::nullopt;
    }
    return newPassword;
}

void StrictModeSection::clearPasswordInputs()
{
    ui->passwordLineEdit->clear();
    ui->newPasswordLineEdit->clear();
    ui->repeatPasswordLineEdit->clear();
}

void StrictModeSection::updateSettingsSectionSize(int index)
{
    QStackedWidget* stack = ui->settingsStrictMode;
    for (int i = 0; i < stack->count(); ++i)
    {
        QWidget* page = stack->widget(i);
        QSizePolicy::Policy policy = (i == index) ? QSizePolicy::Preferred : QSizePolicy::Ignored;
        page->setSizePolicy(policy, policy);
    }
    stack->setCurrentIndex(index);
    stack->updateGeometry();
    adjustSize();
}
