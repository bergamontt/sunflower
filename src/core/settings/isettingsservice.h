#pragma once

#include "lockpolicy.h"

namespace sun::core
{
    class ISettingsService
    {
    public:
        virtual ~ISettingsService() = default;
        LockPolicy lockPolicy() const;
        void setLockPolicy(const LockPolicy& policy);
    private:
        virtual LockPolicy doLockPolicy() const = 0;
        virtual void doSetLockPolicy(const LockPolicy& policy) = 0;
    };

    inline LockPolicy ISettingsService::lockPolicy() const
    {
        return doLockPolicy();
    }

    inline void ISettingsService::setLockPolicy(const LockPolicy& policy)
    {
        doSetLockPolicy(policy);
    }
}
