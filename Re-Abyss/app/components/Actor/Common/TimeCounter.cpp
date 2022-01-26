#include <abyss/components/Actor/Common/TimeCounter.hpp>

namespace abyss::Actor
{
    TimeCounter::TimeCounter(double offset):
        m_totalTime(offset)
    {}
    void TimeCounter::setOffset(double offset)
    {
        m_totalTime += offset;
    }
    void TimeCounter::update(double dt)
    {
        m_totalTime += dt;
    }
    double TimeCounter::getTotalTime() const
    {
        return m_totalTime;
    }
}
