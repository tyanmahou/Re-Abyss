#include "Build.hpp"
#include "Setup/Setup.hpp"
#include "Teardown/Teardown.hpp"
#include "BossMove/BossMove.hpp"
#include <abyss/components/Event/Talk/TriggerFactory.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    void Build(TriggerFactory& triggerTable)
    {
        triggerTable[U"setup"] = [](TalkObj* pTalk){
            pTalk->attach<Setup>(pTalk);
        };
        triggerTable[U"boss_move"] = [](TalkObj* pTalk) {
            pTalk->attach<BossMove>(pTalk);
        };
        triggerTable[U"teardown"] = [](TalkObj* pTalk) {
            pTalk->attach<Teardown>(pTalk);
        };
    }
}
