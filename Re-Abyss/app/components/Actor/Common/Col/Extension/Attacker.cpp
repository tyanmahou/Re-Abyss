#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor::Col
{
	Attacker::Attacker(
        ActorObj* pActor,
        s3d::int32 power,
        double comboDuration,
        double powerReductionRate,
        double invincibleTime
    ) :
        m_pActor(pActor),
        m_power(power),
        m_comboDuration(comboDuration),
        m_powerReductionRate(powerReductionRate),
        m_invincibleTime(invincibleTime)
    {}
    ColSys::ExtData Attacker::data() const
    {
        auto body = m_pActor->find<Body>();
        return Data{
            .power = m_power,
            .pos = body ? body->getCenterPos() : s3d::Vec2::Zero(),
            .velocity = body ? body->getVelocity() : s3d::Vec2::Zero(),
            .comboDuration = m_comboDuration,
            .powerReductionRate = m_powerReductionRate,
            .invincibleTime = m_invincibleTime
        };
    }
}
