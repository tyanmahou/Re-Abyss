#include <abyss/components/Novel/BossTalk0_0/Builder.hpp>

#include <abyss/components/Novel/BossTalk0_0/SignalCtrl.hpp>

#include <abyss/components/Novel/BossTalk0_0/Command/Setup.hpp>
#include <abyss/components/Novel/BossTalk0_0/Command/Teardown.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

namespace abyss::Novel::BossTalk0_0
{
    void Builder::Setup(TalkObj* pTalk)
    {
        pTalk->attach<SignalCtrl>(pTalk);

        pTalk->engine()->addCommand<BossTalk0_0::Setup>();
    }
    void Builder::Teardown(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<BossTalk0_0::Teardown>();
    }
}
