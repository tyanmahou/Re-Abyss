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
            // 揺れてない
            m_offset = Vec2{ 0, 0 };
            return;
        }
        double dt = m_pActor->deltaTime();
        if (dt <= 0) {
            // 更新不要
            return;
        }

        // 時間経過
        m_time -= dt;

        // オフセット計算
        double rate = s3d::Saturate(m_time / m_shakeTime);
        auto periodTime = m_time * m_time * 11.4514;

        // ノイズ
        const double noise = s3d::Periodic::Sine0_1(m_shakeTime, periodTime)
            + s3d::Periodic::Triangle0_1(s3d::Math::InvPi, rate)
            + m_noiseOffset;

        // 左右に往復させるためのオフセット
        double offsetFactor = s3d::Periodic::Triangle0_1(m_shakeTime, periodTime * 5.0);

        m_offset = Vec2::UnitX().rotated(noise * s3d::Math::TwoPi) * (m_maxOffset * offsetFactor) * rate;
    }
    void ShakeCtrl::request(double maxOffset, double timeSec)
    {
        m_time = timeSec;
        m_shakeTime = timeSec;
        m_maxOffset = maxOffset;
        m_noiseOffset = s3d::Random();
    }
}
