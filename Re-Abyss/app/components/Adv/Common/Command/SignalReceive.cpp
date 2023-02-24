#include <abyss/components/Adv/Common/Command/SignalReceive.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv
{
    SignalReceive::SignalReceive(AdvObj* pObj, FunctionType func) :
        m_pObj(pObj),
        m_func(func)
    {}
    void SignalReceive::onStart()
    {
    }
    Coro::Fiber<> SignalReceive::onCommand()
    {
        if (m_func) {
            while (!m_func(m_pObj)){
                co_yield{};
            }
        }
        co_return;
    }
}
