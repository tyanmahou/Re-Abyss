#include <abyss/components/Novel/CodeZeroDemo/Command/AppearEnd.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Novel/Common/TalkCtrl.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    AppearEnd::AppearEnd(TalkObj* pTalk):
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
