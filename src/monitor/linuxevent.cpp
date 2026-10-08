#include "linuxevent.h"

#include <linux/connector.h>
#include <linux/netlink.h>
#include <linux/cn_proc.h>

#include <sys/socket.h>
#include <unistd.h>

#include <fstream>

using namespace std;

namespace sun::monitor
{
    ProcessNetlinkAddress::ProcessNetlinkAddress()
    {
        _addr.nl_family = AF_NETLINK;
        _addr.nl_pid = getpid();
        _addr.nl_groups = CN_IDX_PROC;
    }

    [[nodiscard]] bool ProcessNetlinkAddress::bindTo(const int sock) const
    {
        return bind(sock, reinterpret_cast<const sockaddr*>(&_addr), sizeof(_addr)) >= 0;
    }

    ProcessEventSubscription::ProcessEventSubscription()
            : _buffer(NLMSG_SPACE(sizeof(cn_msg) + sizeof(proc_cn_mcast_op)))
    {
        auto* header = reinterpret_cast<nlmsghdr*>(_buffer.data());
        header->nlmsg_len = NLMSG_LENGTH(sizeof(cn_msg) + sizeof(proc_cn_mcast_op));
        header->nlmsg_type = NLMSG_DONE;
        header->nlmsg_flags = 0;
        header->nlmsg_pid = getpid();

        auto* cn = static_cast<cn_msg*>(NLMSG_DATA(header));
        cn->id.idx = CN_IDX_PROC;
        cn->id.val = CN_VAL_PROC;
        cn->len = sizeof(proc_cn_mcast_op);
        cn->flags = 0;

        auto* operation = reinterpret_cast<proc_cn_mcast_op*>(cn->data);
        *operation = PROC_CN_MCAST_LISTEN;
    }

    [[nodiscard]] bool ProcessEventSubscription::subscribe(const int sock) const
    {
        auto* header = reinterpret_cast<const nlmsghdr*>(_buffer.data());
        iovec iov{
            const_cast<nlmsghdr*>(header),
            header->nlmsg_len
        };

        msghdr message{};
        message.msg_iov = &iov;
        message.msg_iovlen = 1;

        return sendmsg(sock, &message, 0) >= 0;
    }

    bool subscribeToEvents(const int sock)
    {
        ProcessNetlinkAddress address;
        if (!address.bindTo(sock))
        {
            return false;
        }

        ProcessEventSubscription subscription;
        if (!subscription.subscribe(sock))
        {
            return false;
        }

        return true;
    }

    QString getProcessName(const pid_t pid)
    {
        ifstream file("/proc/" + to_string(pid) + "/comm");
        if (!file.is_open())
            return "";
        string name;
        getline(file, name);
        return name.data();
    }

    void createSocket(int& sock)
    {
        if (sock >= 0)
            return;
        sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_CONNECTOR);
    }

    void closeSocket(int& socket)
    {
        if (socket < 0)
            return;
        ::close(socket);
        socket = -1;
    }
}