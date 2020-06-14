#include "IntervalTimeScheduler.hpp"
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>
namespace abyss::cron
{
    IntervalTimeScheduler::IntervalTimeScheduler(const s3d::Duration& duration):
        m_duration(duration)
    {}
    void IntervalTimeScheduler::start()
    {
        auto time = m_pManager->getModule<GlobalTime>();
        auto timeFunc = [time] {return time->timeMicroSec(); };
        m_timer = IntervalTimer(m_duration, true, timeFunc);
    }

    bool IntervalTimeScheduler::update([[maybe_unused]]double dt)
    {
        return m_timer.update();
    }
}
