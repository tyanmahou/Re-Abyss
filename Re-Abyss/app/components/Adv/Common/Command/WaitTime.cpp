#include <abyss/components/Adv/Common/Command/WaitTime.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::Adv
{
    WaitTime::WaitTime(AdvObj* pObj, const s3d::Duration& waitTime) :
        m_pObj(pObj),
        m_waitTime(waitTime)
    {}
    Coro::Fiber<> WaitTime::onCommand()
    {
        return skip() | wait();
    }

    Coro::Fiber<> WaitTime::wait()
    {
        co_await Coro::WaitForSeconds(m_waitTime);
    }
    Coro::Fiber<> WaitTime::skip()
    {
        while (true) {
            if (InputManager::A.down()) {
                co_return;
            }
            co_yield{};
        }
    }
}
