#include "Effects.hpp"

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
}