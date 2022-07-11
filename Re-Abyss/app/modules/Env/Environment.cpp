#include <abyss/modules/Env/Environment.hpp>
#include <abyss/debugs/Debug.hpp>

namespace abyss::Env
{
    void Environment::init(const EnvDesc& desc)
    {
        m_bg = std::make_unique<Bg>();
        if (desc.useSky) {
            m_sky = std::make_unique<Sky>();
        }
        if (desc.useCaustics) {
            m_caustics = std::make_unique<Caustics>();
        }
        if (desc.useWave) {
            m_wave = std::make_unique<Wave>();
        }
        if (desc.useFog) {
            m_fog = std::make_unique<Fog>();
        }
    }
    void Environment::update(double dt)
    {
        if (m_sky) {
            m_sky->update(dt);
        }
        if (m_caustics) {
            m_caustics->update(dt);
        }
        if (m_wave) {
            m_wave->update(dt);
        }
    }
    Fog* Environment::getFog() const
    {
#if ABYSS_DEBUG
        if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::RenderFog)) {
            return nullptr;
        }
#endif
        return m_fog.get();
    }
    void Environment::applyWave(std::function<void()> drawer) const
    {
        if (m_wave) {
            m_wave->apply(drawer);
        } else {
            drawer();
        }
    }
    void Environment::applyFog(std::function<void()> drawer, double z) const
    {
        if (z < 1.0) {
            if (auto fog = this->getFog()) {
                auto fogShader = fog->setZ(z).start();
                drawer();
            } else {
                drawer();
            }
        } else {
            drawer();
        }
    }
}
