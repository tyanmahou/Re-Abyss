#include <abyss/components/Novel/BossTalk0_1/Command/Setup.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Sound/Sound.hpp>

namespace abyss::Novel::BossTalk0_1
{
    Setup::Setup(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}

    void Setup::onStart()
    {
        m_pTalk->getModule<Sound>()->stop(0.5s);
    }

    Coro::Task<> Setup::onCommand()
    {
        co_return;
    }
}
