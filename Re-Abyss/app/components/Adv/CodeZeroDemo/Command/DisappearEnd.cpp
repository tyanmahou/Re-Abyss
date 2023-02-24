#include <abyss/components/Adv/CodeZeroDemo/Command/DisappearEnd.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Adv/Common/TalkCtrl.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    DisappearEnd::DisappearEnd(AdvObj* pTalk) :
        m_pTalk(pTalk)
    {
    }
    void DisappearEnd::onStart()
    {
        m_pTalk->find<TalkCtrl>()->resume();
        m_pTalk->getModule<UIs>()->setFilter(UI::Filter::Always);
    }
    Coro::Fiber<> DisappearEnd::onCommand()
    {
        co_return;
    }
}
