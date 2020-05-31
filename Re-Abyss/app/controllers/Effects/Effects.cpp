#include "Effects.hpp"
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss
{
    Effects::Effects()
    {
        for (auto&& e : m_effects) {
            e = EffectEx(WorldTime::TimeMicroSec);
        }
    }
}
