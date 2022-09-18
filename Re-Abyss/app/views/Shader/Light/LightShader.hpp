#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class LightShader
    {
        class Impl;
    public:
        LightShader();
        ~LightShader();

        const LightShader& setBgColor(const s3d::ColorF& color) const;

        const LightShader& setLightsTexture(const s3d::Texture& lights) const;
        s3d::ScopedCustomShader2D start() const;

    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
