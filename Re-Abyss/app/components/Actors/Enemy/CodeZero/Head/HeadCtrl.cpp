#include "HeadCtrl.hpp"
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
    HeadCtrl::HeadCtrl(ActorObj* pActor):
        m_forward(Forward::None),
        m_pActor(pActor)
    {}
    void HeadCtrl::onStart()
    {
        m_parentCtrl = m_pActor->find<ParentCtrl>();
    }

    s3d::Vec2 HeadCtrl::getPos() const
    {
        return m_parentCtrl->getPos() + Param::Head::Offset;
    }

    void HeadCtrl::setForward(Forward forward)
    {
        m_forward = forward;
    }

    Forward HeadCtrl::getForward() const
    {
        return m_forward;
    }

    s3d::Vec2 HeadCtrl::getCenterPos() const
    {
        return this->getPos() + s3d::Vec2{ 0, 10 };
    }

}

