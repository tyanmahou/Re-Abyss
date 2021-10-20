#include "WaitTime.hpp"
#include <abyss/utils/Coro/Wait/Wait.hpp>
namespace abyss::Novel
{
    WaitTime::WaitTime(TalkObj* pTalk, const s3d::Duration& waitTime) :
        m_pTalk(pTalk),
        m_waitTime(waitTime)
    {}
    Coro::Task<> WaitTime::onCommand()
    {
        co_await Coro::WaitForSeconds(m_waitTime);
    }
}
