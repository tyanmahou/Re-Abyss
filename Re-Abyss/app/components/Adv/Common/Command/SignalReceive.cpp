#include <abyss/components/Adv/Common/Command/SignalReceive.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv
{
    SignalReceive::SignalReceive(AdvObj* pTalk, FunctionType func) :
        m_pTalk(pTalk),
        m_func(func)
    {}
    void SignalReceive::onStart()
    {
    }
    Coro::Fiber<> SignalReceive::onCommand()
    {
        if (m_func) {
            while (!m_func(m_pTalk)){
                co_yield{};
            }
        }
        co_return;
    }
}
