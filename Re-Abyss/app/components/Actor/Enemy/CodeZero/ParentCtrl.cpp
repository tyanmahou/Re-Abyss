#include "ParentCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/Phase1State.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/Phase2State.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/Phase3State.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    ParentCtrl::ParentCtrl(ActorObj* parent):
        m_parent(parent)
    {
    
    }
    void ParentCtrl::onStart()
    {
        m_body = m_parent->find<Actor::Body>();
        m_hp = m_parent->find<HP>();
        m_state = m_parent->find<StateCtrl>();
        m_parts = m_parent->find<PartsCtrl>();
    }
    Ref<HP> ParentCtrl::getHp() const
    {
        return m_hp;
    }
    const s3d::Vec2& ParentCtrl::getPos() const
    {
        return m_body->getPos();
    }

    bool ParentCtrl::isPhase1()const
    {
        return m_state->isState<Phase1State>();
    }
    bool ParentCtrl::isPhase2()const
    {
        return m_state->isState<Phase2State>();
    }
    bool ParentCtrl::isPhase3()const
    {
        return m_state->isState<Phase3State>();
    }
    bool ParentCtrl::isShotCharge() const
    {
        auto left = m_parts->getLeftHand();
        auto right = m_parts->getRightHand();
        return left->isShotCharge() || right->isShotCharge();
    }
}