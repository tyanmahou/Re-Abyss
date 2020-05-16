#include "DamageCallbackModel.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>

namespace abyss::Enemy
{
    DamageCallbackModel::DamageCallbackModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void DamageCallbackModel::setup()
    {
    }

    void DamageCallbackModel::onDamaged()
    {
        m_pActor
            ->find<AudioSourceModel>()
            ->playAt(U"Enemy/damage.wav");
    }

}
