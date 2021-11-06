#include "PostEffects.hpp"

namespace abyss::PostEffect
{
    PostEffects::PostEffects():
        m_scanline(std::make_unique<Scanline>())
    {}

    void PostEffects::update(double dt)
    {
        m_scanline->update(dt);
    }

    Scanline* PostEffects::getScanline() const
    {
        return m_scanline.get();
    }
}
