#pragma once
#include <abyss/controllers/Cron/base/IScheduler.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>

namespace abyss::cron
{
    class IntervalTimeScheduler : public IScheduler
    {
        s3d::Duration m_duration;
        IntervalTimer m_timer;
    public:
        IntervalTimeScheduler(const s3d::Duration& duration);

        void start() override;
        bool update(double dt) override;
    };
}