#include "IntervalTimeScheduler.hpp"
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>

#include <abyss/controllers/Cron/base/IJob.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
namespace abyss::cron
{
    IntervalTimeScheduler::IntervalTimeScheduler(const s3d::Duration& duration):
        m_duration(duration)
    {}

    Coro::Task<> IntervalTimeScheduler::execute(IJob* job)
    {
        auto time = m_pManager->getModule<GlobalTime>();
        auto timeFunc = [time] {return time->timeMicroSec(); };
        while (true) {
            co_yield Coro::WaitForSecondsEx(m_duration, timeFunc);
            co_yield job->onExecute();
        }
    }
}
