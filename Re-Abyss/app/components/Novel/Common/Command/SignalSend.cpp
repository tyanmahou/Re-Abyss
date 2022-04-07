#include <abyss/components/Novel/Common/Command/SignalSend.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel
{
    SignalSend::SignalSend(TalkObj* pTalk, FunctionType func):
        m_pTalk(pTalk),
        m_func(func)
    {}
    void SignalSend::onStart()
    {
        if (m_func) {
            m_func(m_pTalk);
        }
    }
    Coro::Task<> SignalSend::onCommand()
    {
        co_return;
    }
}
