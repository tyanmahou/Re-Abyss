#include <abyss/modules/FieldEnv/Fog/Fog.hpp>

namespace abyss::FieldEnv
{
    const Fog& Fog::setFogColor(const s3d::ColorF& color) const
    {
        m_shader.setFogColor(color);
        return *this;
    }
    const Fog& Fog::setFogFactor(double factor) const
    {
        m_shader.setFogFactor(factor);
        return *this;
    }
    const Fog& Fog::setZ(double z) const
    {
        m_shader.setZ(z);
        return *this;
    }
    s3d::ScopedCustomShader2D Fog::start() const
    {
        return m_shader.start();
    }
}
