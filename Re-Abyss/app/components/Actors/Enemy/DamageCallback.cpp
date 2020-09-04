#include "DamageCallback.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>

namespace abyss::Actor::Enemy
{
    DamageCallback::DamageCallback(IActor* pActor):
        m_pActor(pActor)
    {}

    void DamageCallback::setup()
    {
    }

    void DamageCallback::onDamaged()
    {
        m_pActor
            ->find<AudioSourceModel>()
            ->playAt(U"Damage");
    }

}
