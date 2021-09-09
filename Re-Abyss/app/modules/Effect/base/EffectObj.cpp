#include "EffectObj.hpp"
#include <abyss/components/Common/ClockCtrl.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>
namespace abyss::Effect
{
    EffectObj::EffectObj()
    {
        m_clock = this->attach<ClockCtrl>(this);
    }
    void EffectObj::updateDeltaTime(double dt) const
    {
        m_clock->updateDeltaTime(dt);
    }
    double EffectObj::deltaTime() const
    {
        return m_clock->getDeltaTime();
    }
    double EffectObj::updateTimeSec() const
    {
        return m_clock->getUpdateTimeSec();
    }
    double EffectObj::drawTimeSec() const
    {
        return m_clock->getDrawTimeSec();
    }
    void EffectObj::setTimeScale(double scale)
    {
        m_clock->setTimeScale(scale);
    }
    void EffectObj::update()
    {
        m_clock->updateUpdateTime();
        for (auto&& com : this->finds<IUpdate>()) {
            com->onUpdate();
        }
    }
    void EffectObj::draw()
    {
        m_clock->updateDrawTime();
        auto drawer = this->getModule<DrawManager>();
        auto time = m_clock->getDrawTimeSec();
        bool isActiveAny = false;
        for (auto&& com : this->finds<IDraw>()) {
            bool isActiveCom = !com->isEnd();
            isActiveAny |= isActiveCom;
            if (isActiveCom) {
                drawer->add(m_layer, [com, time] {
                    com->onDraw(time);
                });
            }
        }
        if (!isActiveAny) {
            // 一つも描画しないなら自動破棄
            this->destroy();
        }
    }
}
