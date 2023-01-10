#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/Hand/Builder.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.hpp>
#include <abyss/modules/Actor/Actors.hpp>

namespace abyss::Actor::Enemy::CodeZero
{ 
    PartsCtrl::PartsCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void PartsCtrl::onStart()
    {
        auto* const actors = m_pActor->getModule<Actors>();
        m_leftHand = actors->create<Hand::Builder>(m_pActor, Hand::HandKind::Left)->find<Hand::HandProxy>();
        m_rightHand = actors->create<Hand::Builder>(m_pActor, Hand::HandKind::Right)->find<Hand::HandProxy>();
    }
    void PartsCtrl::setActive(bool active) const
    {
        m_leftHand->getActor()->setActive(active);
        m_rightHand->getActor()->setActive(active);
    }
    void PartsCtrl::setMoveActive(bool active) const
    {
        m_leftHand->setMoveActive(active);
        m_rightHand->setMoveActive(active);
    }
    bool PartsCtrl::isShotCharge() const
    {
        return m_leftHand->isShotCharge() || m_rightHand->isShotCharge();
    }
}
