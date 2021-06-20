#include "ShakeCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor
{
    ShakeCtrl::ShakeCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_offset(0, 0)
    {}

    void ShakeCtrl::onUpdate()
    {
        if (m_shakeTime <= 0 || m_time <= 0) {
            m_offset = Vec2{ 0, 0 };
            return;
        }
        double dt = m_pActor->deltaTime();
        if (dt <= 0) {
            return;
        }
        m_time -= dt;
        double rate = s3d::Saturate(m_time / m_shakeTime);

        auto periodTime = m_time * m_time * 11.4514;
        double noise = s3d::Periodic::Sine0_1(m_shakeTime, periodTime);
        double offsetFactor = s3d::Periodic::Triangle0_1(m_shakeTime, periodTime * 5.0);
        m_offset = Vec2::UnitX().rotated((noise + m_randOffset + s3d::Periodic::Square0_1(s3d::Math::InvPi, rate)) * s3d::Math::TwoPi) * (m_maxOffset * offsetFactor) * rate;
    }
    void ShakeCtrl::request(double maxOffset, double timeSec)
    {
        m_time = timeSec;
        m_shakeTime = timeSec;
        m_maxOffset = maxOffset;
        m_randOffset = s3d::Random();
    }
}
