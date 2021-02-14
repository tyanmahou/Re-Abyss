#include "TimeCtrl.hpp"

namespace abyss::Actor
{
    void TimeCtrl::updateDeltaTime(double dt)
    {
        // TODO timeScaleとかあれば
        m_deltaTime = dt;
    }
    void TimeCtrl::updateUpdateTime()
    {
        m_updateTimeSec += m_deltaTime;
    }
    void TimeCtrl::updateDrawTime()
    {
        m_drawTimeSec += m_deltaTime;
    }
    s3d::Microseconds TimeCtrl::getUpdateTime() const
    {
        return Time::FromSec(m_updateTimeSec);
    }
    double TimeCtrl::getUpdateTimeSec() const
    {
        return m_updateTimeSec;
    }
    s3d::Microseconds TimeCtrl::getDrawTime() const
    {
        return Time::FromSec(m_drawTimeSec);
    }
    double TimeCtrl::getDrawTimeSec() const
    {
        return m_drawTimeSec;
    }

    double TimeCtrl::getDeltaTime() const
    {
        return m_deltaTime;
    }
    void TimeCtrl::resetDrawTime()
    {
        m_drawTimeSec = 0.0;
    }
}
