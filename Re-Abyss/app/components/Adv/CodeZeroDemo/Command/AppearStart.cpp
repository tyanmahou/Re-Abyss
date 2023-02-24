#include <abyss/components/Adv/CodeZeroDemo/Command/AppearStart.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Adv/Common/TalkCtrl.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    AppearStart::AppearStart(AdvObj* pTalk) :
        m_pTalk(pTalk)
    {
    }
    void AppearStart::onStart()
    {
        m_pTalk->find<TalkCtrl>()->request();
        m_pTalk->getModule<UIs>()->setFilter(UI::Filter::Novel);
    }
    Coro::Fiber<> AppearStart::onCommand()
    {
        co_return;
    }
}
