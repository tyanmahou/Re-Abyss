#include "DamageCallbackModel.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
namespace abyss::Enemy
{
    DamageCallbackModel::DamageCallbackModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void DamageCallbackModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }

    void DamageCallbackModel::onDamaged()
    {
        m_pActor
            ->getModule<Sound>()
            ->playSe(U"Enemy/damage.wav", m_body->getPos());
    }

}
