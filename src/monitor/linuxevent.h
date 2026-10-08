#pragma once

#include <QDir>
#include <QFile>

#include <linux/netlink.h>

namespace sun::monitor
{
    class ProcessNetlinkAddress
    {
    public:
        ProcessNetlinkAddress();

        [[nodiscard]] bool bindTo(int sock) const;

    private:
        sockaddr_nl _addr{};
    };

    class ProcessEventSubscription
    {
    public:
        ProcessEventSubscription();

        [[nodiscard]] bool subscribe(int sock) const;

    private:
        std::vector<std::byte> _buffer;
    };

    bool subscribeToEvents(int sock);

    QString getProcessName(pid_t pid);

    void createSocket(int& sock);

    void closeSocket(int& socket);
}
