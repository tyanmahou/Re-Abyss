#include <abyss/components/Novel/Common/Command/SignalReceive.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel
{
    SignalReceive::SignalReceive(TalkObj* pTalk, FunctionType func) :
        m_pTalk(pTalk),
        m_func(func)
    {}
    void SignalReceive::onStart()
    {
    }
    Coro::Task<> SignalReceive::onCommand()
    {
        if (m_func) {
            while (!m_func(m_pTalk)){
                co_yield{};
            }
        }
        co_return;
    }
}
