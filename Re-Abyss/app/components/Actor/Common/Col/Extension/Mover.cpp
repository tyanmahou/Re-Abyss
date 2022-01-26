#include <abyss/components/Actor/Common/Col/Extension/Mover.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor::Col
{
    Mover::Mover(ActorObj* pActor) :
        m_pActor(pActor)
    {}
    ColSys::ExtData Mover::data() const
    {
        auto body = m_pActor->find<Body>();
        return Data{
            .pos = body ? body->getCenterPos() : s3d::Vec2::Zero(),
            .velocity = body ? body->getVelocity() : s3d::Vec2::Zero()
        };
    }
}
