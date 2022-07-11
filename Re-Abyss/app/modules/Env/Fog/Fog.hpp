#pragma once
#include <abyss/views/Shader/Fog/FogShader.hpp>

namespace abyss::Env
{
    /// <summary>
    /// Fog
    /// </summary>
    class Fog
    {
    public:
        const Fog& setFogColor(const s3d::ColorF& color) const;
        const Fog& setFogFactor(double factor) const;
        const Fog& setZ(double z) const;

        [[nodiscard]] s3d::ScopedCustomShader2D start() const;
    private:
        FogShader m_shader;
    };
}
