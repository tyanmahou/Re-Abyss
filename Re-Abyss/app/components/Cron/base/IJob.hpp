#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss::Cron
{
    class IJob
    {
    public:
        virtual ~IJob() = default;

        virtual Coro::Fiber<> onExecute() = 0;
    };
}