#include "Builder.hpp"
#include "Setup/Setup.hpp"
#include "Teardown/Teardown.hpp"
#include "BossMove/BossMove.hpp"

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

namespace abyss::Novel::BossTalk0_0
{
    void Builder::Setup(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<BossTalk0_0::Setup>();
    }
    void Builder::BossMove(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<BossTalk0_0::BossMove>();
    }
    void Builder::Teardown(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<BossTalk0_0::Teardown>();
    }
}
