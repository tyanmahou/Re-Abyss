#pragma once
#include <memory>
#include <Siv3D/ColorF.hpp>
#include <Siv3D/ScopedCustomShader2D.hpp>

namespace abyss
{
    class BlendShader
    {
        class Impl;
    public:
        BlendShader();
        ~BlendShader();
        const BlendShader& setColor(const s3d::ColorF& color) const;
        [[nodiscard]] s3d::ScopedCustomShader2D start() const;
    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
