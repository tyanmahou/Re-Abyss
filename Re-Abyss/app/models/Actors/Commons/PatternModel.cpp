#include "PatternModel.hpp"
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss
{
    PatternModel::PatternModel():
        m_sleep(0.0, true, WorldTime::TimeMicroSec)
    {}
    bool PatternModel::update()
    {
        if (!m_sleep.reachedZero()) {
            return false;
        }
        m_events.pop()();
        return true;
    }
    PatternModel& PatternModel::add(const std::function<void()>& event)
    {
        m_events.add(event);
        m_eventStepNo.push_back(m_events.size() - 1);
        return *this;
    }
    PatternModel& PatternModel::sleep(double time)
    {
        return this->sleep(s3d::Duration(time));
    }
    PatternModel& PatternModel::sleep(const s3d::Duration & time)
    {
        m_events.add([&, time]() {
            m_sleep.restart(time);
        });
        return *this;
    }
    PatternModel& PatternModel::toStep(size_t step)
    {
        m_events.add([&,step]() {
            m_events.set(m_eventStepNo[step]);
        });
        return *this;
    }
}
