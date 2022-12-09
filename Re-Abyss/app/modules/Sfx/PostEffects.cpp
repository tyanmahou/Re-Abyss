#include <abyss/modules/Sfx/PostEffects.hpp>

namespace abyss::Sfx
{
    PostEffects::PostEffects():
        m_pManager(nullptr)
    {}

    void PostEffects::init(const PostEffectsDesc& desc)
    {
        if (desc.useDecorFar) {
            m_decorFar = std::make_unique<DecorFar>();
        }
        if (desc.useBloom) {
            m_bloom = std::make_unique<Bloom>();
            m_bloom->setManager(m_pManager);
        }
        if (desc.useMoisture) {
            m_moisture = std::make_unique<Moisture>();
        }
        if (desc.useBlur) {
            m_blur = std::make_unique<Blur>();
        }
        if (desc.useDeadEffect) {
            m_deadEffect = std::make_unique<DeadEffect>();
        }
        if (desc.useScanline) {
            m_scanline = std::make_unique<Scanline>();
        }
    }

    void PostEffects::setManager(Manager* pManager)
    {
        m_pManager = pManager;
    }
    void PostEffects::update(double dt)
    {
        if (m_decorFar) {
            m_decorFar->update(dt);
        }
        if (m_scanline) [[likely]] {
            m_scanline->update(dt);
        }
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

    DeadEffect* PostEffects::getDeadEffect() const
    {
        return m_deadEffect.get();
    }

    Scanline* PostEffects::getScanline() const
    {
        return m_scanline.get();
    }
}
