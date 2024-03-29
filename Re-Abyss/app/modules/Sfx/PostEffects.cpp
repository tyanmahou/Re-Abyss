#include <abyss/modules/Sfx/PostEffects.hpp>

namespace abyss::Sfx
{
    PostEffects::PostEffects(const PostEffectsDesc& desc) :
        m_pManager(nullptr)
    {
        if (desc.useDecorFar) {
            m_decorFar = std::make_unique<DecorFar>();
        }
        if (desc.useBloom) {
            m_bloom = std::make_unique<Bloom>();
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
        if (desc.useNegaPosiInv) {
            m_negaPosiInv = std::make_unique<NegaPosiInv>();
        }
        if (desc.useScanline) {
            m_scanline = std::make_unique<Scanline>();
        }
    }
    void PostEffects::setManager(Manager* pManager)
    {
        m_pManager = pManager;
        if (m_bloom) {
            m_bloom->setManager(pManager);
        }
    }
    void PostEffects::update(double dt)
    {
        if (m_decorFar) {
            m_decorFar->update(dt);
        }
        if (m_negaPosiInv){
            m_negaPosiInv->update();
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
    NegaPosiInv* PostEffects::getNegaPosiInv() const
    {
        return m_negaPosiInv.get();
    }
    Scanline* PostEffects::getScanline() const
    {
        return m_scanline.get();
    }
}
