#include "Attacker.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor::Collision
{
	Attacker::Attacker(ActorObj* pActor, s3d::int32 power) :
        m_pActor(pActor),
        m_power(power)
    {}
    abyss::Collision::ExtData Attacker::data() const
    {
        auto location = m_pActor->find<ILocator>();
        auto body = m_pActor->find<Body>();
        return Data{
            .power = m_power,
            .pos = location ? location->getCenterPos() : s3d::Vec2::Zero(),
            .velocity = body ? body->getVelocity() : s3d::Vec2::Zero()
        };
    }
}
