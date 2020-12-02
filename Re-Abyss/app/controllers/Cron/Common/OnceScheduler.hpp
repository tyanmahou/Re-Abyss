#pragma once
#include <abyss/controllers/Cron/base/IScheduler.hpp>

namespace abyss::cron
{
    class OnceScheduler : public IScheduler
    {
    public:
        OnceScheduler() = default;

        Coro::Task<> execute(IJob* job) override;
    };
}