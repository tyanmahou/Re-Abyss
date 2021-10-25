#include "ClearMessage.hpp"

namespace abyss::Novel
{
    ClearMessage::ClearMessage(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}
    void ClearMessage::onStart()
    {
    
    }
    Coro::Task<> ClearMessage::onCommand()
    {
        co_return;
    }
}
