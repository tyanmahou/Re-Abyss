#include <abyss/components/Novel/Common/Command/Signal.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel
{
    Signal::Signal(TalkObj* pTalk, FunctionType func):
        m_pTalk(pTalk),
        m_func(func)
    {}
    void Signal::onStart()
    {
        if (m_func) {
            m_func(m_pTalk);
        }
    }
    Coro::Task<> Signal::onCommand()
    {
        co_return;
    }
}
