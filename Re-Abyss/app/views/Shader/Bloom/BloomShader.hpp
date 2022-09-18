#pragma once
#pragma once
#include <memory>
#include <Siv3D/ScopedCustomShader2D.hpp>

namespace abyss
{
    class BloomShader
    {
        class Impl;
    public:
        BloomShader();
        ~BloomShader();

        const BloomShader& setLightColor(const s3d::ColorF& color) const;
        void apply(const s3d::Texture& tex) const;
    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
