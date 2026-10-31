#ifndef STRICTMODESECTION_H
#define STRICTMODESECTION_H

#include <QFrame>

#include <memory>

#include "settings/isettingsservice.h"
#include "password/ipasswordservice.h"

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
    std::unique_ptr<sun::core::ISettingsService> settingsService;
    std::unique_ptr<sun::core::IPasswordService> passwordService;

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

private:
    int previousComboIndex = 0;
};

#endif // STRICTMODESECTION_H
