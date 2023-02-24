#include <abyss/components/Adv/Common/Command/ClearMessage.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>

namespace abyss::Adv
{
    ClearMessage::ClearMessage(AdvObj* pTalk):
        m_pTalk(pTalk)
    {}
    void ClearMessage::onStart()
    {
        m_pTalk->engine()->clearMessage();
    }
    Coro::Fiber<> ClearMessage::onCommand()
    {
        co_return;
    }
}
