#include "Environment.hpp"

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
    }
    void Environment::update(double dt)
    {
        if (m_sky) {
            m_sky->update(dt);
        }
        if (m_waterSurface) {
            m_waterSurface->update(dt);
        }
    }
}
