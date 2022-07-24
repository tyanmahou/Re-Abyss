#include <abyss/components/Novel/CodeZeroDemo/Command/DisappearStart.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Novel/Common/TalkCtrl.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    DisappearStart::DisappearStart(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {
    }
    void DisappearStart::onStart()
    {
        m_pTalk->getModule<Sound>()->stop(0.5s);
        m_pTalk->find<TalkCtrl>()->request();
        m_pTalk->getModule<UIs>()->setFilter(UI::Filter::Novel);
    }
    Coro::Task<> DisappearStart::onCommand()
    {
        co_return;
    }
}
