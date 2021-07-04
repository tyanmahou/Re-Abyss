#include "ClockCtrl.hpp"

namespace abyss::Actor
{
    void ClockCtrl::updateDeltaTime(double dt)
    {        
        m_deltaTime = dt * m_timeScale;
    }
    void ClockCtrl::updateUpdateTime()
    {
        m_updateTimeSec += m_deltaTime;
    }
    void ClockCtrl::updateDrawTime()
    {
        m_drawTimeSec += m_deltaTime;
    }
    void ClockCtrl::setTimeScale(double timeScale)
    {
        m_timeScale = timeScale;
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
