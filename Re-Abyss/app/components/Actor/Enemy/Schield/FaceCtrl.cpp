#include <abyss/components/Actor/Enemy/Schield/FaceCtrl.hpp>

#include <Siv3D.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/params/Actor/Enemy/Schield/Param.hpp>

namespace abyss::Actor::Enemy::Schield
{
    FaceCtrl::FaceCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void FaceCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }
    s3d::Circle FaceCtrl::getCollider() const
    {
        s3d::Vec2 offset{ 53.0 * m_body->getForward(), 16 };
        return s3d::Circle(m_body->getPos() + offset, Param::Wait::FaceColRadius);
    }

}
