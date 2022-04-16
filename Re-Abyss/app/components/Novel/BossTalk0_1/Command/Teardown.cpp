#include <abyss/components/Novel/BossTalk0_1/Command/Teardown.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel::BossTalk0_1
{
    Teardown::Teardown(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {}

    void Teardown::onStart()
    {
    }

    Coro::Task<> Teardown::onCommand()
    {
        co_return;
    }
}