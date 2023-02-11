#include <abyss/components/Actor/Common/ShakeCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor
{
    ShakeCtrl::ShakeCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_offset(0, 0)
    {}

    void ShakeCtrl::onUpdate()
    {
        double dt = m_pActor->deltaTime();
        if (dt <= 0) {
            // 更新不要
            return;
        }
        if (!this->isShakeing()) {
            // 揺れてない
            m_offset = Vec2{ 0, 0 };
            return;
        }

        m_elapsedSec += dt;
        double radiusRate = m_timeSec <= 0 ? 1.0 : Max(1.0 - m_elapsedSec / m_timeSec, 0.0);

        constexpr Fps baseFps = 120_fps;
        if (m_elapsedSec >= m_nextTargetTimeSec) {
            constexpr double nextDiff = baseFps.deltaTime();
            m_nextTargetTimeSec = static_cast<int32>(m_elapsedSec / nextDiff) * nextDiff + nextDiff;
            m_offsetTarget = s3d::RandomVec2(Circle(m_maxOffset * radiusRate));
        }
        m_offset = s3d::Math::Lerp(m_offset, m_offsetTarget, InterpUtil::DampRatio(0.99, dt, baseFps));
    }
    void ShakeCtrl::request(double maxOffset, double timeSec)
    {
        m_maxOffset = maxOffset;
        m_timeSec = timeSec;
        m_elapsedSec = 0;
        m_nextTargetTimeSec = 0;
    }
    bool ShakeCtrl::isShakeing() const
    {
        if (m_timeSec <= 0) {
            return false;
        }
        return m_elapsedSec <= m_timeSec;
    }
}
