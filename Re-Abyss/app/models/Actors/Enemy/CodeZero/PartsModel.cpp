#include "PartsModel.hpp"

#include <abyss/controllers/Actors/Enemy/CodeZero/Head/HeadActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>
#include <abyss/controllers/World/World.hpp>

namespace abyss::Actor::CodeZero
{ 
    PartsModel::PartsModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void PartsModel::setup()
    {}

    void PartsModel::onStart()
    {
        auto* const world = m_pActor->getModule<World>();

        m_head = world->create<Head::HeadActor>(m_pActor);
        m_leftHand = world->create<Hand::HandActor>(m_pActor, Hand::HandActor::Kind::Left);
        m_rightHand = world->create<Hand::HandActor>(m_pActor, Hand::HandActor::Kind::Right);
    }
    void PartsModel::setActive(bool active) const
    {
        m_head->setActive(active);
        m_leftHand->setActive(active);
        m_rightHand->setActive(active);
    }
}
