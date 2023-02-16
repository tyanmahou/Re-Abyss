#include <abyss/utils/Shake/SimpleShake.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include "SimpleShake.hpp"

namespace abyss::Shake
{
    SimpleShake::SimpleShake()
    {
    }
    void SimpleShake::update(double dt, double erpRate)
    {
        if (dt <= 0) {
            // 更新不要
            return;
        }
        if (this->isEnd()) {
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
        m_offset = s3d::Math::Lerp(m_offset, m_offsetTarget, InterpUtil::DampRatio(erpRate, dt, baseFps));
    }
    void SimpleShake::request(double maxOffset, double timeSec)
    {
        m_maxOffset = maxOffset;
        m_timeSec = timeSec;
        m_elapsedSec = 0;
        m_nextTargetTimeSec = 0;
        m_isStop = false;
    }
    void SimpleShake::stop()
    {
        m_isStop = true;
    }
    bool SimpleShake::isShakeing() const
    {
        if (m_isStop) {
            return false;
        }
        if (m_timeSec < 0) {
            // 無限ゆれ
            return true;
        }
        if (m_timeSec <= 0) {
            return false;
        }
        return m_elapsedSec <= m_timeSec;
    }
    bool SimpleShake::isEnd() const
    {
        return !m_shake.isShakeing();
    }
}
