#pragma once

namespace sun::blocker
{
    template <typename T>
    class Blocker
    {
    public:
        virtual ~Blocker() = default;

        virtual bool blockApplication(T id) = 0;
    };
}