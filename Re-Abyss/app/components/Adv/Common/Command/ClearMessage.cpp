#include <abyss/components/Adv/Common/Command/ClearMessage.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/SentenceCtrl.hpp>

namespace abyss::Adv
{
    ClearMessage::ClearMessage(AdvObj* pObj):
        m_pObj(pObj)
    {}
    void ClearMessage::onStart()
    {
        m_pObj->sentence()->clearMessage();
    }
    Coro::Fiber<> ClearMessage::onCommand()
    {
        co_return;
    }
}
