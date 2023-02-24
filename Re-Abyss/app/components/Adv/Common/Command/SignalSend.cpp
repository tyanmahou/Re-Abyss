#include <abyss/components/Adv/Common/Command/SignalSend.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv
{
    SignalSend::SignalSend(AdvObj* pTalk, FunctionType func):
        m_pTalk(pTalk),
        m_func(func)
    {}
    void SignalSend::onStart()
    {
        if (m_func) {
            m_func(m_pTalk);
        }
    }
    Coro::Fiber<> SignalSend::onCommand()
    {
        co_return;
    }
}
