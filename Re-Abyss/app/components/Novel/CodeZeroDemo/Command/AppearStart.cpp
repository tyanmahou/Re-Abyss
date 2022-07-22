#include <abyss/components/Novel/CodeZeroDemo/Command/AppearStart.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/UI/UIs.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    AppearStart::AppearStart(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {
    }
    void AppearStart::onStart()
    {
        m_pTalk->getModule<UIs>()->setFilter(UI::Filter::Novel);
    }
    Coro::Task<> AppearStart::onCommand()
    {
        co_return;
    }
}
