#include <abyss/components/Adv/CodeZeroDemo/Command/DisappearStart.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Adv/Common/TalkCtrl.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    DisappearStart::DisappearStart(AdvObj* pTalk) :
        m_pTalk(pTalk)
    {
    }
    void DisappearStart::onStart()
    {
        m_pTalk->find<TalkCtrl>()->request();
        m_pTalk->getModule<UIs>()->setFilter(UI::Filter::Novel);
    }
    Coro::Fiber<> DisappearStart::onCommand()
    {
        co_return;
    }
}
