#include <abyss/components/Actor/Player/DamageCallback.hpp>

#include <abyss/components/Actor/Player/State/DamageState.hpp>
#include <abyss/components/Actor/utils/StatePriority.hpp>

namespace abyss::Actor::Player
{
    DamageCallback::DamageCallback(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void DamageCallback::onDamaged(const DamageData& damage)
    {
        m_pActor->find<StateCtrl>()
            ->changeState<DamageState, StatePriority::Damage>(
            m_pActor->find<Body>()->getCenterPos() - damage.pos
            );
    }
}
