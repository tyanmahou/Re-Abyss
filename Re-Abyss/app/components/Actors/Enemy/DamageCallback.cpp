#include "DamageCallback.hpp"
#include <abyss/modules/System/System.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>

namespace abyss::Actor::Enemy
{
    DamageCallback::DamageCallback(IActor* pActor):
        m_pActor(pActor)
    {}

    void DamageCallback::setup()
    {
    }

    void DamageCallback::onDamaged([[maybe_unused]]const DamageData& damage)
    {
        m_pActor
            ->find<AudioSource>()
            ->playAt(U"Damage");
    }

}
