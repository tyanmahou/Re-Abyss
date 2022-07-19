#include <abyss/components/Novel/Common/Command/Stash.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel
{
    Stash::Stash(TalkObj* pTalk):
        m_pTalk(pTalk)
    {
    }
    void Stash::onStart()
    {
        m_pTalk->stash();
    }
    Coro::Task<> Stash::onCommand()
    {
        co_yield{};
    }
}
