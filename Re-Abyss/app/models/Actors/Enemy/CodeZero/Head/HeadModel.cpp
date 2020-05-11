#include "HeadModel.hpp"
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>

namespace abyss::CodeZero::Head
{
    HeadModel::HeadModel(IActor* pActor):
        m_forward(Forward::None),
        m_pActor(pActor)
    {}
    void HeadModel::setup()
    {
        m_parentCtrl = m_pActor->find<ParentCtrlModel>();
    }

    s3d::Vec2 HeadModel::getPos() const
    {
        return m_parentCtrl->getPos() + Param::Head::Offset;
    }

    void HeadModel::setForward(Forward forward)
    {
        m_forward = forward;
    }

    Forward HeadModel::getForward() const
    {
        return m_forward;
    }

}

