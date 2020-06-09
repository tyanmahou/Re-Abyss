#include "QuakeModel.hpp"

#include <Siv3D.hpp>

#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/TimeController/TimeController.hpp>

namespace abyss
{
    QuakeModel::QuakeModel(Manager* pManager, double maxOffset, double timeSec) :
        m_maxOffset(maxOffset),
        m_timeSec(timeSec),
        m_stopwatch(true, [pManager]() {return pManager->getModule<TimeController>()->timeMicroSec(); }),
        m_pManager(pManager)
    {}
    bool QuakeModel::IsEnd() const
    {
        if (m_timeSec <= 0) {
            return false;
        }
        return m_stopwatch.sF() > m_timeSec;
    }
    s3d::Vec2 QuakeModel::apply(const s3d::Vec2& pos)const
    {
        if (m_pManager->getModule<TimeController>()->isPuase()) {
            return pos;
        }
        double radiusRate = m_timeSec <= 0 ? 1.0 : Max(1.0 - m_stopwatch.sF() / m_timeSec, 0.0);
        const Vec2 offset = s3d::RandomVec2(Circle(m_maxOffset * radiusRate));
        return pos + offset;
    }
}
