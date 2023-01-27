#pragma once
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss::Novel
{
    class ICommand
    {
    public:
        virtual ~ICommand() = default;

        virtual void onStart() {}
        virtual void onEnd() {}
        virtual Coro::Fiber<> onCommand() = 0;
    };
}