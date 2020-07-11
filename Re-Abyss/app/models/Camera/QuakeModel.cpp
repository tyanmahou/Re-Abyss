#include "QuakeModel.hpp"

#include <Siv3D.hpp>

#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>

namespace abyss
{
    QuakeModel::QuakeModel(Manager* pManager, double maxOffset, double timeSec) :
        m_maxOffset(maxOffset),
        m_timeSec(timeSec),
        m_stopwatch(true, [pManager]() {return pManager->getModule<GlobalTime>()->timeMicroSec(); }),
        m_intervalTimer(0.017s, true),
        m_pManager(pManager)
    {
        m_intervalTimer.toEnd();
    }
    bool QuakeModel::IsEnd() const
    {
        if (m_timeSec <= 0) {
            return false;
        }
        return m_stopwatch.sF() > m_timeSec;
    }
    s3d::Vec2 QuakeModel::apply(const s3d::Vec2& pos)
    {
        if (m_pManager->getModule<GlobalTime>()->isPuase()) {
            return pos + m_offset;
        }
        if (m_intervalTimer.update()) {
            double radiusRate = m_timeSec <= 0 ? 1.0 : Max(1.0 - m_stopwatch.sF() / m_timeSec, 0.0);
            m_offset = s3d::RandomVec2(Circle(m_maxOffset * radiusRate));
        }
        return pos + m_offset;
    }
}
