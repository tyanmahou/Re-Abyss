#include "ClockCtrl.hpp"
#include "ITimeScale.hpp"
#include <abyss/utils/Clock/ClockUtil.hpp>
namespace abyss
{
    ClockCtrl::ClockCtrl(GameObject* pObj):
        m_pObj(pObj),
        m_updateClock(this),
        m_drawClock(this)
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
    void ClockCtrl::setTimeScale(double timeScale)
    {
        m_timeScaleBase = timeScale;
    }
    void ClockCtrl::updateUpdateTime()
    {
        m_updateTimeSec += m_deltaTime;
    }
    void ClockCtrl::updateDrawTime()
    {
        m_drawTimeSec += m_deltaTime;
    }
    s3d::Microseconds ClockCtrl::getUpdateTime() const
    {
        return ClockUtil::FromSec(m_updateTimeSec);
    }
    double ClockCtrl::getUpdateTimeSec() const
    {
        return m_updateTimeSec;
    }
    s3d::ISteadyClock* ClockCtrl::getUpdateClock()
    {
        return &m_updateClock;
    }
    s3d::Microseconds ClockCtrl::getDrawTime() const
    {
        return ClockUtil::FromSec(m_drawTimeSec);
    }
    double ClockCtrl::getDrawTimeSec() const
    {
        return m_drawTimeSec;
    }

    s3d::ISteadyClock* ClockCtrl::getDrawClock()
    {
        return &m_drawClock;
    }

    double ClockCtrl::getDeltaTime() const
    {
        return m_deltaTime;
    }
    void ClockCtrl::resetDrawTime()
    {
        m_drawTimeSec = 0.0;
    }
}
