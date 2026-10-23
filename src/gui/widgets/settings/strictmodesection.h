#ifndef STRICTMODESECTION_H
#define STRICTMODESECTION_H

#include <QFrame>

#include "settings/settingsservice.h"
#include "password/passwordservice.h"

namespace Ui {
class StrictModeSection;
}

class StrictModeSection : public QFrame
{
    Q_OBJECT

public:
    explicit StrictModeSection(QWidget *parent = nullptr);
    ~StrictModeSection();

private:
    Ui::StrictModeSection *ui;
    sun::core::SettingsService settingsService;
    sun::core::PasswordService passwordService;

private slots:
    void onLockTypeChanged(int index);
    void onSaveClicked();
    void onDelayChanged(int seconds);

private:
    void updateSettingsSectionSize(int index);
    void updatePasswordSettings(bool hasPassword);
    void loadCurrentSettings();

private:
    void clearPasswordInputs();
    std::optional<QString> handleCreatePassword();
    std::optional<QString> handleUpdatePassword(const QString& currentHash);
};

#endif // STRICTMODESECTION_H
