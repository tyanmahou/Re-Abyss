#include "ClockCtrl.hpp"
#include "ITimeScale.hpp"
#include <abyss/utils/Clock/ClockUtil.hpp>
namespace abyss
{
    ClockCtrl::ClockCtrl(GameObject* pObj):
        m_pObj(pObj)
    {}
    void ClockCtrl::onStart()
    {
        m_timeScaleComps = m_pObj->finds<ITimeScale>();
    }
    void ClockCtrl::updateDeltaTime(double dt)
    {
        m_timeScale = m_timeScaleBase;
        for (const auto& comp : m_timeScaleComps) {
            if (comp) {
                m_timeScale *= comp->timeScale();
            }
        }
        m_deltaTime = dt * m_timeScale;
    }
    double ClockCtrl::getDeltaTime() const
    {
        return m_deltaTime;
    }
    void ClockCtrl::setTimeScale(double timeScale)
    {
        m_timeScaleBase = timeScale;
    }
    void ClockCtrl::updateTime()
    {
        m_timeSec += m_deltaTime;
    }
    s3d::Microseconds ClockCtrl::getTime() const
    {
        return ClockUtil::FromSec(m_timeSec);
    }
    double ClockCtrl::getTimeSec() const
    {
        return m_timeSec;
    }
    s3d::ISteadyClock* ClockCtrl::getClock()
    {
        return this;
    }
    void ClockCtrl::resetTime()
    {
        m_timeSec = 0.0;
    }
    s3d::uint64 ClockCtrl::getMicrosec()
    {
        return this->getTime().count();
    }
}
