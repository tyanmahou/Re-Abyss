#include <abyss/components/Novel/BossTalk0_0/Command/Setup.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/Novel/Common/MessageBox.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/CodeZeroProxy.hpp>

namespace abyss::Novel::BossTalk0_0
{
    Setup::Setup(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}

    void Setup::onStart()
    {
    }

    Coro::Task<> Setup::onCommand()
    {
        co_return;
    }
}
