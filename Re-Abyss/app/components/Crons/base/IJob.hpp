#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::cron
{
    class IJob
    {
    public:
        virtual ~IJob() = default;

        virtual Coro::Task<> onExecute() = 0;
    };
}