#include "ParentCtrlModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/State/Phase1State.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/State/Phase2State.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/State/Phase3State.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/PartsModel.hpp>


namespace abyss::CodeZero
{
    ParentCtrlModel::ParentCtrlModel(IActor* parent):
        m_parent(parent)
    {
    
    }
    void ParentCtrlModel::setup()
    {
        m_body = m_parent->find<BodyModel>();
        m_hp = m_parent->find<HPModel>();
        m_state = m_parent->find<StateModel>();
        m_parts = m_parent->find<PartsModel>();
    }
    Ref<HPModel> ParentCtrlModel::getHp() const
    {
        return m_hp;
    }
    const s3d::Vec2& ParentCtrlModel::getPos() const
    {
        return m_body->getPos();
    }

    bool ParentCtrlModel::isPhase1()const
    {
        return m_state->isState<Phase1State>();
    }
    bool ParentCtrlModel::isPhase2()const
    {
        return m_state->isState<Phase2State>();
    }
    bool ParentCtrlModel::isPhase3()const
    {
        return m_state->isState<Phase3State>();
    }
    bool ParentCtrlModel::isShotCharge() const
    {
        auto left = m_parts->getLeftHand();
        auto right = m_parts->getRightHand();
        return left->isShotCharge() || right->isShotCharge();
    }
}