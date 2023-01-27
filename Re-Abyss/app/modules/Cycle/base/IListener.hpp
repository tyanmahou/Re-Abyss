#pragma once

namespace abyss::Cycle
{
    class IListener
    {
    public:
        virtual ~IListener() = default;

        virtual bool listen() = 0;
    };
}