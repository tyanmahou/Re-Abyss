#include <abyss/components/Adv/Common/Command/SignalSend.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv
{
    SignalSend::SignalSend(AdvObj* pObj, FunctionType func):
        m_pObj(pObj),
        m_func(func)
    {}
    void SignalSend::onStart()
    {
        if (m_func) {
            m_func(m_pObj);
        }
    }
    Coro::Fiber<> SignalSend::onCommand()
    {
        co_return;
    }
}
