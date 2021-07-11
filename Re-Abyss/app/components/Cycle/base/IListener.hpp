#pragma once

namespace abyss::Cycle
{
    class IListener
    {
    public:
        virtual ~IListener() = default;

        virtual void listen() = 0;
    };
}