#include <abyss/modules/Sfx/PostEffects.hpp>

namespace abyss::Sfx
{
    PostEffects::PostEffects():
        m_pManager(nullptr),
        m_scanline(std::make_unique<Scanline>()),
        m_blur(std::make_unique<Blur>()),
        m_bloom(std::make_unique<Bloom>())
    {}

    void PostEffects::setManager(Manager* pManager)
    {
        m_pManager = pManager;
        if (m_bloom) {
            m_bloom->setManager(pManager);
        }
    }
    void PostEffects::update(double dt)
    {
        m_scanline->update(dt);
    }

    Bloom* PostEffects::getBloom() const
    {
        return m_bloom.get();
    }

    Blur* PostEffects::getBlur() const
    {
        return m_blur.get();
    }

    Scanline* PostEffects::getScanline() const
    {
        return m_scanline.get();
    }
}
