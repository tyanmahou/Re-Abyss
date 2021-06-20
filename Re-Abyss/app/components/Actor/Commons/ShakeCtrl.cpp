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

        m_offset = Vec2::UnitX().rotated(m_noise.noise0_1(m_time * 100.0) * s3d::Math::TwoPi) * m_maxOffset * rate;
    }
    void ShakeCtrl::request(double maxOffset, double timeSec)
    {
        m_time = timeSec;
        m_shakeTime = timeSec;
        m_maxOffset = maxOffset;
        m_noise.reseed(s3d::Random(0u, UINT32_MAX));
    }
}
