#include "EffectsHolder.hpp"
#include <abyss/modules/Effects/base/EffectObj.hpp>

namespace abyss::Effect
{
    void EffectsHolder::flush()
    {
        if (m_reserves.empty()) {
            return;
        }
        // startでregistされてもいいようにここでmove
        auto registing = std::move(m_reserves);
        m_reserves.clear();
        for (auto& obj : registing) {
            obj->setup();
            obj->start();
            m_effects.push_back(std::move(obj));
        }
    }
    void EffectsHolder::push(const std::shared_ptr<EffectObj>&effect)
    {
        m_reserves.push_back(effect);
    }
    void EffectsHolder::update()
    {
        for (auto& obj : m_effects) {
            if (!obj->isActive()) {
                continue;
            }
            obj->update();
        }
    }
    void EffectsHolder::draw() const
    {
        for (auto& obj : m_effects) {
            if (!obj->isActive()) {
                continue;
            }
            obj->draw();
        }
    }
    void EffectsHolder::erase()
    {
        s3d::Erase_if(m_effects, [](const std::shared_ptr<EffectObj>& obj) {
            if (obj->isDestroyed()) {
                obj->end();
                return true;
            }
            return false;
        });
    }
    void EffectsHolder::clear()
    {
        m_reserves.clear();
        for (auto&& obj : m_effects) {
            obj->end();
        }
        m_effects.clear();
    }
}
