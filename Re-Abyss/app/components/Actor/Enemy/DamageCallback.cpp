#include "DamageCallback.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/AudioSource.hpp>

namespace abyss::Actor::Enemy
{
    DamageCallback::DamageCallback(ActorObj* pActor):
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
