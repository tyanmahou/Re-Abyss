#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/ScopedCustomShader2D.hpp>

namespace abyss
{
    class ScanlineShader
    {
        class Impl;
    public:
        ScanlineShader();
        ~ScanlineShader();

        const ScanlineShader& setTime(double time) const;
        const ScanlineShader& setTextureSize(const s3d::Vec2& size) const;

        s3d::ScopedCustomShader2D start() const;

    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
