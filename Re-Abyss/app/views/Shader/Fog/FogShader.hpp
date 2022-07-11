#pragma once
#include <memory>
#include <Siv3D/ScopedCustomShader2D.hpp>

namespace abyss
{
    class FogShader
    {
        class Impl;
    public:
        FogShader();

        const FogShader& setFogColor(const s3d::ColorF& color) const;
        const FogShader& setFogFactor(double factor) const;
        const FogShader& setZ(double z) const;

        [[nodiscard]] s3d::ScopedCustomShader2D start() const;
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}
