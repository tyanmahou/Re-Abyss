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
        while (true) {
            co_await Coro::WaitForSeconds(m_duration, time);
            co_await task();
        }
    }
}
