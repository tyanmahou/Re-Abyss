#include "WaitTime.hpp"
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::Novel
{
    WaitTime::WaitTime(TalkObj* pTalk, const s3d::Duration& waitTime) :
        m_pTalk(pTalk),
        m_waitTime(waitTime)
    {}
    Coro::Task<> WaitTime::onCommand()
    {
        return skip() | wait();
    }

    Coro::Task<> WaitTime::wait()
    {
        co_await Coro::WaitForSeconds(m_waitTime);
    }
    Coro::Task<> WaitTime::skip()
    {
        while (true) {
            if (InputManager::A.down()) {
                co_return;
            }
            co_yield{};
        }
    }
}
