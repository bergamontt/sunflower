#pragma once

#include <sys/types.h>

namespace sun::blocker
{
    class Blocker
    {
    public:
        virtual ~Blocker() = default;

        virtual bool blockProcess(pid_t pid) = 0;
    };
}