#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class OutLineShader
    {
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    public:
        OutLineShader();

        const OutLineShader& setTextureSize(const s3d::Vec2& size) const;
        const OutLineShader& setOutLineSize(double size) const;
        const OutLineShader& setColor(const s3d::ColorF color) const;

        s3d::ScopedCustomShader2D start() const;
    };
}