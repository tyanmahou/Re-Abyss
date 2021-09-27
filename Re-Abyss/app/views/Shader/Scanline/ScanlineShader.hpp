#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class ScanlineShader
    {
        class Impl;
    public:
        ScanlineShader();

        const ScanlineShader& setTime(double time) const;
        const ScanlineShader& setTexturSize(const s3d::Vec2& size) const;

        s3d::ScopedCustomShader2D start() const;

    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}