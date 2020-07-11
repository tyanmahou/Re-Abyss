#include "IntervalTimer.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    class IntervalTimer::Impl
    {
        Duration m_timeSec;
        TimerEx m_timer;
        bool m_onReachedZero = false;
    public:
        Impl(double timeSec, bool startImmediately, TimeGetFunction_t timeGetter):
            m_timeSec(timeSec),
            m_timer(timeSec, startImmediately, timeGetter)
        {}
        Impl(const s3d::Duration& time, bool startImmediately, TimeGetFunction_t timeGetter) :
            m_timeSec(time),
            m_timer(time, startImmediately, timeGetter)
        {}
        bool toEnd()
        {
            m_timer.set(0.0s);
        }
        bool update()
        {
            if (m_timer.reachedZero()) {
                m_timer.restart(m_timeSec);
                m_onReachedZero = true;
                return true;
            }
            m_onReachedZero = false;
            return false;
        }
        bool onRestart() const
        {
            return m_onReachedZero;
        }
    };
    IntervalTimer::IntervalTimer(double timeSec, bool startImmediately, TimeGetFunction_t timeGetter) :
        m_pImpl(std::make_shared<Impl>(timeSec, startImmediately, timeGetter))
    {}

    IntervalTimer::IntervalTimer(const s3d::Duration & time, bool startImmediately, TimeGetFunction_t timeGetter) :
        m_pImpl(std::make_shared<Impl>(time, startImmediately, timeGetter))
    {}

    bool IntervalTimer::update() const
    {
        return m_pImpl->update();
    }

    bool IntervalTimer::onRestart() const
    {
        return m_pImpl->onRestart();
    }

    bool IntervalTimer::toEnd() const
    {
        return m_pImpl->toEnd();
    }



}
