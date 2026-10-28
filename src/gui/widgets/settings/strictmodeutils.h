#pragma once

#include "settings/settingsservice.h"

namespace sun::gui
{
    sun::core::LockType indexToLockType(int index)
    {
        switch (index)
        {
            case 1:  return sun::core::LockType::Password;
            case 2:  return sun::core::LockType::Delay;
            default: return sun::core::LockType::None;
        }
    }

    int lockTypeToIndex(sun::core::LockType type)
    {
        switch (type)
        {
            case sun::core::LockType::Password: return 1;
            case sun::core::LockType::Delay:    return 2;
            case sun::core::LockType::None:     return 0;
        }
        return 0;
    }
} // sun::gui