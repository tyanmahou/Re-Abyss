#pragma once
#include <memory>
#include <Siv3D/ScopedCustomShader2D.hpp>

namespace abyss
{
    class RgbShiftShader
    {
        class Impl;
    public:
        RgbShiftShader();
        ~RgbShiftShader();

        s3d::ScopedCustomShader2D start() const;

    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
