#include <abyss/components/Adv/CodeZeroDemo/Command/AppearEnd.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Adv/Common/TalkCtrl.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    AppearEnd::AppearEnd(AdvObj* pTalk):
        m_pTalk(pTalk)
    {
    }
    void AppearEnd::onStart()
    {
        m_pTalk->find<TalkCtrl>()->resume();
        m_pTalk->getModule<UIs>()->setFilter(UI::Filter::Always);
    }
    Coro::Fiber<> AppearEnd::onCommand()
    {
        co_return;
    }
}
