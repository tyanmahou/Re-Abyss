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
        m_pManager(pManager)
    {
    }

    void QuakeModel::update()
    {
        if (m_pManager->getModule<GlobalTime>()->isPuase()) {
            return;
        }

        double radiusRate = m_timeSec <= 0 ? 1.0 : Max(1.0 - m_stopwatch.sF() / m_timeSec, 0.0);
        m_offset = s3d::RandomVec2(Circle(m_maxOffset * radiusRate));
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
        return m_stopwatch.sF() > m_timeSec;
    }
    const s3d::Vec2& QuakeModel::getOffset() const
    {
        return m_offset;
    }
}
