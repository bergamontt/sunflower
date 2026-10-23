#pragma once

#include "lockpolicy.h"

namespace sun::core
{
    class SettingsService
    {
    public:
        LockPolicy lockPolicy() const;
        void setLockPolicy(const LockPolicy& policy);
    };
}