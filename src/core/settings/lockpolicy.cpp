#include "lockpolicy.h"

namespace sun::core
{
    LockPolicy LockPolicy::none()
    {
        return LockPolicy(LockType::None, {});
    }

    LockPolicy LockPolicy::password(const QString& hash)
    {
        return LockPolicy(LockType::Password, hash);
    }

    LockPolicy LockPolicy::delay(int seconds)
    {
        return LockPolicy(LockType::Delay, seconds);
    }

    LockType LockPolicy::lockType() const
    {
        return type;
    }

    QString LockPolicy::hash() const
    {
        return type == LockType::Password ? value.toString() : QString{};
    }

    int LockPolicy::delay() const
    {
        return type == LockType::Delay ? value.toInt() : 0;
    }

    LockPolicy::LockPolicy(LockType type, QVariant value)
        : type(type)
        , value(std::move(value))
    {}
}