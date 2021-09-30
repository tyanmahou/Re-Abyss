#include "EffectObj.hpp"
#include <abyss/components/Common/ClockCtrl.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>
#include <abyss/components/Effect/base/Drawer.hpp>

namespace abyss::Effect
{
    EffectObj::EffectObj()
    {
        m_clock = this->attach<ClockCtrl>(this);
        m_drawer = this->attach<Drawer>(this);
    }
    void EffectObj::updateDeltaTime(double dt) const
    {
        m_clock->updateDeltaTime(dt);
        if (this->isActive()) {
            m_clock->updateUpdateTime();
        }
    }
    double EffectObj::deltaTime() const
    {
        return m_clock->getDeltaTime();
    }
    double EffectObj::timeSec() const
    {
        return m_clock->getUpdateTimeSec();
    }
    void EffectObj::setTimeScale(double scale)
    {
        m_clock->setTimeScale(scale);
    }
    void EffectObj::update()
    {
        for (auto&& com : this->finds<IUpdate>()) {
            com->onUpdate();
        }
    }
    void EffectObj::draw()
    {
        m_drawer->draw();
    }
}
