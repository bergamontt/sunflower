#pragma once

#include "settings/isettingsservice.h"

namespace sun::core
{
    class SettingsService : public ISettingsService
    {
    private:
        LockPolicy doLockPolicy() const override;
        void doSetLockPolicy(const LockPolicy& policy) override;
    };
}
