#include "Build.hpp"
#include "Setup/Setup.hpp"
#include "Teardown/Teardown.hpp"
#include "BossMove/BossMove.hpp"
#include <abyss/modules/Event/Talk/base/TriggerManager.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    void Build(TriggerManager& manager)
    {
        manager[U"setup"] = [] {
            return std::make_unique<Setup>();
        };
        manager[U"boss_move"] = [] {
            return std::make_unique<BossMove>();
        };
        manager[U"teardown"] = [] {
            return std::make_unique<Teardown>();
        };
    }
}
