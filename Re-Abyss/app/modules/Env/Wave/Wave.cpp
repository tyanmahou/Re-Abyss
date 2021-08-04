#include "Wave.hpp"

namespace abyss::Env
{
    void Wave::update(double dt)
    {
        m_time += dt;
        m_shader.setTime(m_time);
    }
    void Wave::apply(std::function<void()> drawer) const
    {
        m_shader.apply(drawer);
    }
}
