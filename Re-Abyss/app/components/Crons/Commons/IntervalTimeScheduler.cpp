#include "IntervalTimeScheduler.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

#include <abyss/utils/Coro/Task/Task.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

namespace abyss::Cron
{
    IntervalTimeScheduler::IntervalTimeScheduler(Manager* pManager, const s3d::Duration& duration):
        m_pManager(pManager),
        m_duration(duration)
    {}

    Coro::Task<> IntervalTimeScheduler::execute(std::function<Coro::Task<>()> task)
    {
        auto time = m_pManager->getModule<GlobalTime>();
        auto timeFunc = [time] {return time->timeMicroSec(); };
        while (true) {
            co_yield Coro::WaitForSecondsEx(m_duration, timeFunc);
            co_yield task();
        }
    }
}
