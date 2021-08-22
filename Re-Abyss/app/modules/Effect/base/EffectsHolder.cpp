#include "EffectsHolder.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>

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
            if (obj->isDestroyed()) {
                // 最初から死んでる
                continue;
            }
            obj->setup();
            obj->start();
            if (obj->isDestroyed()) {
                // 即破棄されたら即死ぬ
                obj->end();
            } else {
                m_effects.push_back(std::move(obj));
            }
        }
    }
    void EffectsHolder::push(const std::shared_ptr<EffectObj>&effect)
    {
        m_reserves.push_back(effect);
    }
    void EffectsHolder::updateDeltaTime(double dt)
    {
        for (auto& obj : m_effects) {
            obj->updateDeltaTime(dt);
        }
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
    size_t EffectsHolder::size() const
    {
        return m_effects.size();
    }
}
