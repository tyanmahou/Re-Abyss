#include "DamageCallback.hpp"
#include <abyss/components/Actors/Player/State/DamageState.hpp>
#include <abyss/components/Actors/utils/StatePriority.hpp>

namespace abyss::Actor::Player
{
    DamageCallback::DamageCallback(IActor* pActor):
        m_pActor(pActor)
    {}

    void DamageCallback::onDamaged(const DamageData& damage)
    {
        m_pActor->find<StateCtrl>()
            ->changeState<DamageState, StatePriority::Damage>(damage.velocity);
    }
}
