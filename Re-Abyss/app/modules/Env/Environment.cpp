#include <abyss/modules/Env/Environment.hpp>

namespace abyss::Env
{
    void Environment::init(const EnvDesc& desc)
    {
        m_bg = std::make_unique<Bg>();
        if (desc.useSky) {
            m_sky = std::make_unique<Sky>();
        }
        if (desc.useWaterSurface) {
            m_waterSurface = std::make_unique<WaterSurface>();
        }
        if (desc.useWave) {
            m_wave = std::make_unique<Wave>();
        }
    }
    void Environment::update(double dt)
    {
        if (m_sky) {
            m_sky->update(dt);
        }
        if (m_waterSurface) {
            m_waterSurface->update(dt);
        }
        if (m_wave) {
            m_wave->update(dt);
        }
    }
    void Environment::applyWave(std::function<void()> drawer) const
    {
        if (m_wave) {
            m_wave->apply(drawer);
        } else {
            drawer();
        }
    }
}
