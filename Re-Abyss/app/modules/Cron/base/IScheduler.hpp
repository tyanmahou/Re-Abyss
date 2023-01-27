#pragma once
#include <functional>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss::Cron
{
    class IScheduler
    {
    public:
        virtual ~IScheduler() = default;
        virtual Coro::Fiber<> execute(std::function<Coro::Fiber<>()> task) = 0;
    };
}