#pragma once
#include <abyss/modules/Cron/base/IScheduler.hpp>

namespace abyss::cron
{
    class IntervalTimeScheduler : public IScheduler
    {
        s3d::Duration m_duration;
    public:
        IntervalTimeScheduler(const s3d::Duration& duration);

        Coro::Task<> execute(IJob* job) override;
    };
}