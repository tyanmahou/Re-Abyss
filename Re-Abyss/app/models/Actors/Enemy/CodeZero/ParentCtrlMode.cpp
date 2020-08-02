#include "ParentCtrlModel.hpp"
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>

#include <abyss/models/Actors/Enemy/CodeZero/State/Phase1State.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/State/Phase2State.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/State/Phase3State.hpp>


namespace abyss::CodeZero
{
    ParentCtrlModel::ParentCtrlModel(CodeZeroActor* parent):
        m_parent(parent)
    {
    
    }
    void ParentCtrlModel::setup()
    {
        m_hp = m_parent->find<HPModel>();
        m_state = m_parent->find<StateModel>();
    }
    Ref<HPModel> ParentCtrlModel::getHp() const
    {
        return m_hp;
    }
    const s3d::Vec2& ParentCtrlModel::getPos() const
    {
        return m_parent->getPos();
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
}