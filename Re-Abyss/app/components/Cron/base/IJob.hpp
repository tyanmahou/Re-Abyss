#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Cron
{
    class IJob
    {
    public:
        virtual ~IJob() = default;

        virtual Coro::Task<> onExecute() = 0;
    };
}