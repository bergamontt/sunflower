#pragma once

#include "blocker.h"

#include <sys/types.h>

namespace sun::blocker
{
    class LinuxBlocker final : public Blocker
    {
    public:
        ~LinuxBlocker() override = default;

        bool blockProcess(pid_t pid) override;
    };
}