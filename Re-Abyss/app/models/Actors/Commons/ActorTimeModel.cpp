#include "ActorTimeModel.hpp"

namespace abyss
{
    void ActorTimeModel::update(double dt)
    {
        // TODO timeScaleとかあれば
        m_deltaTime = dt;
        m_totalTimeSec += m_deltaTime;
    }
    s3d::Microseconds ActorTimeModel::getTime() const
    {
        return Time::FromSec(m_totalTimeSec);
    }
    double ActorTimeModel::getDeltaTime() const
    {
        return m_deltaTime;
    }
}
