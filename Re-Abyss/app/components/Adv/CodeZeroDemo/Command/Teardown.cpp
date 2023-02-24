#include <abyss/components/Adv/CodeZeroDemo/Command/Teardown.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Event/GameClear/Builder.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    Teardown::Teardown(AdvObj* pObj) :
        m_pObj(pObj)
    {}

    void Teardown::onStart()
    {
        m_pObj->getModule<UIs>()->setFilter(UI::Filter::Adv);
        m_pObj->getModule<Events>()->create<Event::GameClear::Builder>();
    }

    Coro::Fiber<> Teardown::onCommand()
    {
        co_return;
    }
}
