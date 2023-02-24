#include <abyss/components/Adv/Common/Command/ShakeTag.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>

namespace abyss::Adv
{
    ShakeTag::ShakeTag(AdvObj* pObj, bool isShake) :
        m_pObj(pObj),
        m_isShake(isShake)
    {}
    void ShakeTag::onStart()
    {
        m_pObj->engine()->setIsShake(m_isShake);
    }
    Coro::Fiber<> ShakeTag::onCommand()
    {
        co_return;
    }
}
