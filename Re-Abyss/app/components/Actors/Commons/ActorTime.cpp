#include "ActorTime.hpp"

namespace abyss
{
    void ActorTime::updateDeltaTime(double dt)
    {
        // TODO timeScaleとかあれば
        m_deltaTime = dt;
    }
    void ActorTime::updateUpdateTime()
    {
        m_updateTimeSec += m_deltaTime;
    }
    void ActorTime::updateDrawTime()
    {
        m_drawTimeSec += m_deltaTime;
    }
    s3d::Microseconds ActorTime::getUpdateTime() const
    {
        return Time::FromSec(m_updateTimeSec);
    }
    double ActorTime::getUpdateTimeSec() const
    {
        return m_updateTimeSec;
    }
    s3d::Microseconds ActorTime::getDrawTime() const
    {
        return Time::FromSec(m_drawTimeSec);
    }
    double ActorTime::getDrawTimeSec() const
    {
        return m_drawTimeSec;
    }

    double ActorTime::getDeltaTime() const
    {
        return m_deltaTime;
    }
    void ActorTime::resetDrawTime()
    {
        m_drawTimeSec = 0.0;
    }
}
