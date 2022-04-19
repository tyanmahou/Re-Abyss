#include <abyss/components/Novel/BossTalk0_1/Command/Teardown.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Event/Events.hpp>

#include <abyss/components/Event/GameClear/Builder.hpp>

namespace abyss::Novel::BossTalk0_1
{
    Teardown::Teardown(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {}

    void Teardown::onStart()
    {
        m_pTalk->getModule<Events>()->create<Event::GameClear::Builder>();
    }

    Coro::Task<> Teardown::onCommand()
    {
        co_return;
    }
}