#include "Scanline.hpp"

namespace abyss::PostEffect
{
    void Scanline::update(double dt)
    {
        m_time += dt;
        m_scanline.setTime(m_time);
    }
    s3d::ScopedCustomShader2D Scanline::start() const
    {
        return m_scanline.start();
    }
}
