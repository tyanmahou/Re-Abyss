#include "ClockCtrl.hpp"

namespace abyss::decor
{
    void ClockCtrl::updateDeltaTime(double dt)
    {
        // TODO timeScaleとかあれば
        m_deltaTime = dt;
    }
    void ClockCtrl::updateUpdateTime()
    {
        m_updateTimeSec += m_deltaTime;
    }
    void ClockCtrl::updateDrawTime()
    {
        m_drawTimeSec += m_deltaTime;
    }
    s3d::Microseconds ClockCtrl::getUpdateTime() const
    {
        return Clock::FromSec(m_updateTimeSec);
    }
    double ClockCtrl::getUpdateTimeSec() const
    {
        return m_updateTimeSec;
    }
    s3d::Microseconds ClockCtrl::getDrawTime() const
    {
        return Clock::FromSec(m_drawTimeSec);
    }
    double ClockCtrl::getDrawTimeSec() const
    {
        return m_drawTimeSec;
    }

    double ClockCtrl::getDeltaTime() const
    {
        return m_deltaTime;
    }
    void ClockCtrl::resetDrawTime()
    {
        m_drawTimeSec = 0.0;
    }
}
