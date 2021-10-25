#include "ClearMessage.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

namespace abyss::Novel
{
    ClearMessage::ClearMessage(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}
    void ClearMessage::onStart()
    {
        m_pTalk->engine()->clearMessage();
    }
    Coro::Task<> ClearMessage::onCommand()
    {
        co_return;
    }
}
