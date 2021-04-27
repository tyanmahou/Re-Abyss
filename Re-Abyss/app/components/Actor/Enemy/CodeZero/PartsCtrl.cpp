#include "PartsCtrl.hpp"

#include <abyss/components/Actor/Enemy/CodeZero/Head/Builder.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/Builder.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.h>
#include <abyss/modules/World/World.hpp>

namespace abyss::Actor::Enemy::CodeZero
{ 
    PartsCtrl::PartsCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void PartsCtrl::onStart()
    {
        auto* const world = m_pActor->getModule<World>();

        m_head = world->create<Head::Builder>(m_pActor);
        m_leftHand = world->create<Hand::Builder>(m_pActor, Hand::HandKind::Left)->find<Hand::HandProxy>();
        m_rightHand = world->create<Hand::Builder>(m_pActor, Hand::HandKind::Right)->find<Hand::HandProxy>();
    }
    void PartsCtrl::setActive(bool active) const
    {
        m_head->setActive(active);
        m_leftHand->getActor()->setActive(active);
        m_rightHand->getActor()->setActive(active);
    }
}
