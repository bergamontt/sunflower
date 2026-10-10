#pragma once

#include "blocker.h"

#include <sys/types.h>

namespace sun::blocker
{
    class LinuxBlocker final : public Blocker<pid_t>
    {
    public:
        ~LinuxBlocker() override = default;

        bool blockApplication(pid_t id) override;
    };
}