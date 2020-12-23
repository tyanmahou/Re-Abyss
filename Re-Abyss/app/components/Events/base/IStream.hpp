#pragma once
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Event
{
    class IStream
    {
    public:
        virtual ~IStream() = default;

        virtual Coro::Task<> onExecute() = 0;
    };
}