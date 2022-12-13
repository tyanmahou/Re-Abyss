#include <abyss/components/Novel/CodeZeroDemo/Command/Teardown.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Event/GameClear/Builder.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    Teardown::Teardown(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {}

    void Teardown::onStart()
    {
        m_pTalk->getModule<UIs>()->setFilter(UI::Filter::Novel);
        m_pTalk->getModule<Events>()->create<Event::GameClear::Builder>();
    }

    Coro::Fiber<> Teardown::onCommand()
    {
        co_return;
    }
}
