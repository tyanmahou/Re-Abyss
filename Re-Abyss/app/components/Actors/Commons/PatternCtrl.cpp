#include "PatternCtrl.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
namespace abyss::Actor
{
    PatternCtrl::PatternCtrl()
    {}
    PatternCtrl::PatternCtrl(IActor * pActor):
        m_pActor(pActor)
    {}

    void PatternCtrl::setup()
    {
        if (m_pActor) {
            m_sleep = TimerEx(0.0, true, [this]() {return m_pActor->getUpdateTime(); });
        }
    }
    bool PatternCtrl::update()
    {
        if (!m_sleep.reachedZero()) {
            return false;
        }
        if (m_events.size() == 0) {
            return false;
        }
        m_events.pop()();
        return true;
    }
    PatternCtrl& PatternCtrl::add(const std::function<void()>& event)
    {
        m_events.add(event);
        m_eventStepNo.push_back(m_events.size() - 1);
        return *this;
    }
    PatternCtrl& PatternCtrl::sleep(double time)
    {
        return this->sleep(s3d::Duration(time));
    }
    PatternCtrl& PatternCtrl::sleep(const s3d::Duration & time)
    {
        m_events.add([this, time]() {
            m_sleep.restart(time);
        });
        return *this;
    }
    PatternCtrl& PatternCtrl::toStep(size_t step)
    {
        m_events.add([this, step]() {
            m_events.set(m_eventStepNo[step]);
        });
        return *this;
    }
    PatternCtrl& PatternCtrl::toStep(size_t step, size_t count)
    {
        m_toStepCount.push_back(0);
        size_t index = m_toStepCount.size() - 1;
        m_events.add([this, step, index, count]() {
            if (++m_toStepCount[index] <= count) {
                m_events.set(m_eventStepNo[step]);
            } else {
                m_toStepCount[index] = 0;
            }
        });
        return *this;
    }
    PatternCtrl& PatternCtrl::clear()
    {
        m_events.clear();
        m_eventStepNo.clear();
        m_toStepCount.clear();
        return *this;
    }
}
