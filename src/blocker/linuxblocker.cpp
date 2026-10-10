#include "linuxblocker.h"

#include <csignal>

namespace sun::blocker
{
    bool LinuxBlocker::blockApplication(pid_t pid)
    {
        if (pid <= 0)
            return false;

        return ::kill(pid, SIGSTOP) == 0;
    }
}
