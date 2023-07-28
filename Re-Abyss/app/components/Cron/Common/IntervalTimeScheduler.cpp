#include <abyss/components/Cron/Common/IntervalTimeScheduler.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>

namespace abyss::Cron
{
    IntervalTimeScheduler::IntervalTimeScheduler(Manager* pManager, const s3d::Duration& duration):
        m_pManager(pManager),
        m_duration(duration)
    {}

    Coro::Fiber<> IntervalTimeScheduler::execute(std::function<Coro::Fiber<>()> task)
    {
        auto time = m_pManager->getModule<GlobalTime>();
        while (true) {
            co_await Coro::FiberUtil::WaitForSeconds(m_duration, time);
            co_await task();
        }
    }
}
