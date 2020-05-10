#include "ParentCtrlModel.hpp"
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>

namespace abyss::CodeZero
{
    ParentCtrlModel::ParentCtrlModel(CodeZeroActor* parent):
        m_parent(parent)
    {
    
    }
    void ParentCtrlModel::setup()
    {
        m_hp = m_parent->find<HPModel>();
    }
    Ref<HPModel> ParentCtrlModel::getHp() const
    {
        return m_hp;
    }
    const s3d::Vec2& ParentCtrlModel::getPos() const
    {
        return m_parent->getPos();
    }
}