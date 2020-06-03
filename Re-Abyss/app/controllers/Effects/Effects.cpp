#include "Effects.hpp"
#include <abyss/controllers/TimeController/TimeController.hpp>
namespace abyss
{
    Effects::Effects()
    {
    }
    void Effects::init(const TimeController& time)
    {
        for (auto&& e : m_effects) {
            e = EffectEx([&time] {return time.timeMicroSec(); });
        }
    }
}
