#include "Effects.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Common/SivEffect.hpp>

namespace abyss::Effect
{
    void Effects::updateAll(double dt)
    {
        m_effects.flush();
        m_effects.updateDeltaTime(dt);
        m_effects.update();
        m_effects.erase();
    }
    void Effects::draw() const
    {
        m_effects.draw();
    }
    size_t Effects::size() const
    {
        return m_effects.size();
    }
    void Effects::clear()
    {
        m_effects.clear();
    }
    Ref<EffectObj> Effects::create(DrawLayer layer)
    {
        auto obj = std::make_shared<EffectObj>();
        obj->setLayer(layer);
        return this->regist(obj);
    }
    Ref<EffectObj> Effects::regist(const std::shared_ptr<EffectObj>& effect)
    {
        effect->setManager(m_pManager);
        m_effects.push(effect);
        return effect;
    }
    Ref<EffectObj> Effects::regist(std::unique_ptr<s3d::IEffect>&& effect, DrawLayer layer)
    {
        auto obj = this->create(layer);
        obj->attach<SivEffect>(std::move(effect));
        return obj;
    }
}