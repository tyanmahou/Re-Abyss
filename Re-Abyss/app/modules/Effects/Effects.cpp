#include "Effects.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
namespace abyss
{
    Effects::Effects()
    {
    }
    void Effects::setManager(Manager* pManager)
    {
        for (auto&& e : m_effects) {
            e = EffectEx([pManager] {return pManager->getModule<GlobalTime>()->timeMicroSec(); });
        }
    }
}
