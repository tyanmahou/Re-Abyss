#pragma once
#include <abyss/views/Shader/Scanline/ScanlineShader.hpp>

namespace abyss::Sfx
{
    class Scanline
    {
    public:
        void update(double dt);
        s3d::ScopedCustomShader2D start() const;
    private:
        double m_time = 0.0;
        ScanlineShader m_scanline;
    };
}