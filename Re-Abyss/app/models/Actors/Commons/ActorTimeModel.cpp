#include "ActorTimeModel.hpp"

namespace abyss
{
    void ActorTimeModel::updateDeltaTime(double dt)
    {
        // TODO timeScaleとかあれば
        m_deltaTime = dt;
    }
    void ActorTimeModel::updateUpdateTime()
    {
        m_updateTimeSec += m_deltaTime;
    }
    void ActorTimeModel::updateDrawTime()
    {
        m_drawTimeSec += m_deltaTime;
    }
    s3d::Microseconds ActorTimeModel::getUpdateTime() const
    {
        return Time::FromSec(m_updateTimeSec);
    }
    double ActorTimeModel::getUpdateTimeSec() const
    {
        return m_updateTimeSec;
    }
    s3d::Microseconds ActorTimeModel::getDrawTime() const
    {
        return Time::FromSec(m_drawTimeSec);
    }
    double ActorTimeModel::getDrawTimeSec() const
    {
        return m_drawTimeSec;
    }

    double ActorTimeModel::getDeltaTime() const
    {
        return m_deltaTime;
    }
    void ActorTimeModel::resetDrawTime()
    {
        m_drawTimeSec = 0.0;
    }
}
