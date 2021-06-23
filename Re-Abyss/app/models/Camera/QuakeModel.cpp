#include "QuakeModel.hpp"
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    QuakeModel::QuakeModel(double maxOffset, double timeSec) :
        m_maxOffset(maxOffset),
        m_timeSec(timeSec)
    {}

    void QuakeModel::update(double dt)
    {
        if (dt <= 0.0) {
            return;
        }
        m_elapsedSec += dt;
        double radiusRate = m_timeSec <= 0 ? 1.0 : Max(1.0 - m_elapsedSec / m_timeSec, 0.0);
        if (m_elapsedSec >= m_nextTargetTimeSec) {
            m_nextTargetTimeSec += (1.0 / 60.0);
            m_offsetTarget = s3d::RandomVec2(Circle(m_maxOffset * radiusRate));
        }
        m_offset = s3d::Math::Lerp(m_offset, m_offsetTarget, InterpUtil::DampRatio(0.7, dt));
    }
    void QuakeModel::stop()
    {
        m_isStop = true;
    }
    bool QuakeModel::isEnd() const
    {
        if (m_isStop) {
            return true;
        }
        if (m_timeSec <= 0) {
            return false;
        }
        return m_elapsedSec > m_timeSec;
    }
    const s3d::Vec2& QuakeModel::getOffset() const
    {
        return m_offset;
    }
}
