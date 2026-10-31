#ifndef PASSWORDCONFIRMATION_H
#define PASSWORDCONFIRMATION_H

#include <QDialog>

#include "password/ipasswordservice.h"
#include "settings/isettingsservice.h"

#include <memory>

namespace Ui {
class PasswordConfirmation;
}

class PasswordConfirmation : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordConfirmation(QWidget *parent = nullptr);
    ~PasswordConfirmation();

private slots:
    void onConfirm();

private:
    Ui::PasswordConfirmation *ui;

private:
    std::unique_ptr<sun::core::IPasswordService> passwordService;
    std::unique_ptr<sun::core::ISettingsService> settingService;
};

#endif // PASSWORDCONFIRMATION_H
