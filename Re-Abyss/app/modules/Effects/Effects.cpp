#include "Effects.hpp"
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
namespace abyss
{
    Effects::Effects()
    {
    }
    void Effects::init(const GlobalTime& time)
    {
        for (auto&& e : m_effects) {
            e = EffectEx([&time] {return time.timeMicroSec(); });
        }
    }
}
