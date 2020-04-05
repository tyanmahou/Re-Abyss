#include "TimeCounterModel.hpp"
namespace abyss
{
    TimeCounterModel::TimeCounterModel(double offset):
        m_totalTime(offset)
    {}
    void TimeCounterModel::setOffset(double offset)
    {
        m_totalTime += offset;
    }
    void TimeCounterModel::update(double dt)
    {
        m_totalTime += dt;
    }
    double TimeCounterModel::getTotalTime() const
    {
        return m_totalTime;
    }
}
