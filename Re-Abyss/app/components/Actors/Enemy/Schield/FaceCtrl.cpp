#include "FaceCtrl.hpp"

#include <Siv3D.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>

namespace abyss::Actor::Enemy::Schield
{
    FaceCtrl::FaceCtrl(IActor* pActor):
        m_pActor(pActor)
    {}
    void FaceCtrl::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }
    s3d::Circle FaceCtrl::getCollider() const
    {
        s3d::Vec2 offset{ 53.0 * m_body->getForward(), 16 };
        return s3d::Circle(m_body->getPos() + offset, Param::Wait::FaceColRadius);
    }

}
