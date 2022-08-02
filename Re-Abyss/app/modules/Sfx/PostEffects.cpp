#include <abyss/modules/Sfx/PostEffects.hpp>

namespace abyss::Sfx
{
    PostEffects::PostEffects():
        m_pManager(nullptr),
        m_decorFar(std::make_unique<DecorFar>()),
        m_bloom(std::make_unique<Bloom>()),
        m_moisture(std::make_unique<Moisture>()),
        m_blur(std::make_unique<Blur>()),
        m_scanline(std::make_unique<Scanline>())
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
        m_decorFar->update(dt);
        m_scanline->update(dt);
    }

    Moisture* PostEffects::getMoisture() const
    {
        return m_moisture.get();
    }

    DecorFar* PostEffects::getDecorFar() const
    {
        return m_decorFar.get();
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
