#include <abyss/components/Novel/Common/Command/ShakeTag.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Novel/base/Engine.hpp>

namespace abyss::Novel
{
    ShakeTag::ShakeTag(TalkObj* pTalk, bool isShake) :
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
