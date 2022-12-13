#pragma once
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss::Event
{
    class IStream
    {
    public:
        virtual ~IStream() = default;

        virtual Coro::Fiber<> onExecute() = 0;
    };
}