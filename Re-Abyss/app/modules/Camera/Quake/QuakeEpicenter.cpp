#include <abyss/modules/Camera/Quake/QuakeEpicenter.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    QuakeEpicenter::QuakeEpicenter(double maxOffset, double timeSec) :
        m_maxOffset(maxOffset),
        m_timeSec(timeSec),
        m_offset(0, 0),
        m_offsetTarget(0, 0)
    {}

    void QuakeEpicenter::update(double dt)
    {
        if (dt <= 0.0) {
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
    void QuakeEpicenter::stop()
    {
        m_isStop = true;
    }
    bool QuakeEpicenter::isEnd() const
    {
        if (m_isStop) {
            return true;
        }
        if (m_timeSec <= 0) {
            return false;
        }
        return m_elapsedSec > m_timeSec;
    }
    const s3d::Vec2& QuakeEpicenter::getOffset() const
    {
        return m_offset;
    }
}
