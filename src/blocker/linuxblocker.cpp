#include "linuxblocker.h"

#include <csignal>

namespace sun::blocker
{
    bool LinuxBlocker::blockApplication(pid_t id)
    {
        if (id <= 0)
            return false;

        return ::kill(id, SIGSTOP) == 0;
    }
}
