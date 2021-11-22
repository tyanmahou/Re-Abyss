#include "Attacker.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor::Col
{
	Attacker::Attacker(ActorObj* pActor, s3d::int32 power) :
        m_pActor(pActor),
        m_power(power)
    {}
    ColSys::ExtData Attacker::data() const
    {
        auto body = m_pActor->find<Body>();
        return Data{
            .power = m_power,
            .pos = body ? body->getCenterPos() : s3d::Vec2::Zero(),
            .velocity = body ? body->getVelocity() : s3d::Vec2::Zero()
        };
    }
}
