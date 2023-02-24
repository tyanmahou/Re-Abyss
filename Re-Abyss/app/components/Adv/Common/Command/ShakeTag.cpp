#include <abyss/components/Adv/Common/Command/ShakeTag.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>

namespace abyss::Adv
{
    ShakeTag::ShakeTag(AdvObj* pTalk, bool isShake) :
        m_pTalk(pTalk),
        m_isShake(isShake)
    {}
    void ShakeTag::onStart()
    {
        m_pTalk->engine()->setIsShake(m_isShake);
    }
    Coro::Fiber<> ShakeTag::onCommand()
    {
        co_return;
    }
}
