#include "settingsservice.h"
#include "settingskeys.h" 

#include <QSettings>

namespace sun::core
{   
    LockPolicy SettingsService::lockPolicy() const
    {
        QSettings settings;
        settings.beginGroup(settings::restrictions);
        const int type = settings.value(settings::type_key, static_cast<int>(LockType::None)).toInt();
        const QVariant value = settings.value(settings::type_key);
        settings.endGroup();
        switch (static_cast<LockType>(type))
        {
            case LockType::Password:
                return LockPolicy::password(value.toString());
            case LockType::Delay:
                return LockPolicy::delay(value.toInt());
            case LockType::None:
            default:
                return LockPolicy::none();
        }
    }

    void SettingsService::setLockPolicy(const LockPolicy& policy)
    {
        QSettings settings;
        settings.beginGroup(settings::restrictions);
        settings.clear();
        settings.setValue(settings::type_key, static_cast<int>(policy.lockType()));
        switch (policy.lockType())
        {
            case LockType::Password:
                settings.setValue(settings::value_key, policy.hash());
                break;
            case LockType::Delay:
                settings.setValue(settings::value_key, policy.delay());
                break;
            case LockType::None:
                break;
        }
        settings.endGroup();
    }
}