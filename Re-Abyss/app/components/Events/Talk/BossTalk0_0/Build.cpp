#include "Build.hpp"
#include "Setup/Setup.hpp"
#include "Teardown/Teardown.hpp"
#include "BossMove/BossMove.hpp"
#include <abyss/components/Events/Talk/TriggerFactory.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    void Build(TriggerFactory& triggerTable)
    {
        //triggerTable[U"setup"] = [] {
        //    return std::make_unique<Setup>();
        //};
        //triggerTable[U"boss_move"] = [] {
        //    return std::make_unique<BossMove>();
        //};
        //triggerTable[U"teardown"] = [] {
        //    return std::make_unique<Teardown>();
        //};
    }
}
