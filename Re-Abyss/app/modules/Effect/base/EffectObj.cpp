#include <abyss/modules/Effect/base/EffectObj.hpp>

#include <abyss/modules/DrawManager/DrawManager.hpp>
#include <abyss/components/Common/ClockCtrl.hpp>
#include <abyss/modules/Effect/base/IUpdate.hpp>
#include <abyss/modules/Effect/base/IDraw.hpp>
#include <abyss/modules/Effect/base/Drawer.hpp>

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
            m_clock->updateTime();
        }
    }
    double EffectObj::deltaTime() const
    {
        return m_clock->getDeltaTime();
    }
    double EffectObj::timeSec() const
    {
        return m_clock->getTimeSec();
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
        auto drawer = this->getModule<DrawManager>();
        for (auto&& com : this->finds<IDraw>()) {
            drawer->add(com->getLayer(), [com] {
                com->onDraw();
            }, com->getOrder());
        }
    }
    DrawLayer EffectObj::getLayer() const
    {
        return m_drawer->getLayer();
    }
    EffectObj& EffectObj::setLayer(DrawLayer layer)
    {
        m_drawer->setLayer(layer);
        return *this;
    }

    double EffectObj::getOrder() const
    {
        return m_drawer->getOrder();
    }
    EffectObj& EffectObj::setOrder(double order)
    {
        m_drawer->setOrder(order);
        return *this;
    }
}
