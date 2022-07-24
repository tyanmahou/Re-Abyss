#include <abyss/components/Novel/CodeZeroDemo/Command/DisappearEnd.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Novel/Common/TalkCtrl.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    DisappearEnd::DisappearEnd(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {
    }
    void DisappearEnd::onStart()
    {
        m_pTalk->find<TalkCtrl>()->resume();
        m_pTalk->getModule<UIs>()->setFilter(UI::Filter::Always);
    }
    Coro::Task<> DisappearEnd::onCommand()
    {
        co_return;
    }
}
