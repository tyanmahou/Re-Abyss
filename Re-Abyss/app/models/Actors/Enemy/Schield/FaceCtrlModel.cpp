#include "FaceCtrlModel.hpp"

#include <Siv3D.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>

namespace abyss::Actor::Enemy::Schield
{
    FaceCtrlModel::FaceCtrlModel(IActor* pActor):
        m_pActor(pActor)
    {}
    void FaceCtrlModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }
    s3d::Circle FaceCtrlModel::getCollider() const
    {
        s3d::Vec2 offset{ 53.0 * m_body->getForward(), 16 };
        return s3d::Circle(m_body->getPos() + offset, Param::Wait::FaceColRadius);
    }

}
