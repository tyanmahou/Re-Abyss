#pragma once
#include <functional>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Cron
{
    class IScheduler
    {
    public:
        virtual ~IScheduler() = default;
        virtual Coro::Task<> execute(std::function<Coro::Task<>()> task) = 0;
    };
}