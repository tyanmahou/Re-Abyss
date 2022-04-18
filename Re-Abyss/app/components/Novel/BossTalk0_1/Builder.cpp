#include <abyss/components/Novel/BossTalk0_1/Builder.hpp>

#include <abyss/components/Novel/BossTalk0_1/SignalCtrl.hpp>

#include <abyss/components/Novel/BossTalk0_1/Command/Setup.hpp>
#include <abyss/components/Novel/BossTalk0_1/Command/Teardown.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

namespace abyss::Novel::BossTalk0_1
{
    void Builder::Setup(TalkObj* pTalk)
    {
        pTalk->attach<SignalCtrl>(pTalk);

        pTalk->engine()->addCommand<BossTalk0_1::Setup>();
    }
    void Builder::Teardown(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<BossTalk0_1::Teardown>();
    }
}
