#include <abyss/modules/Sfx/Blur/Blur.hpp>

namespace abyss::Sfx
{
    s3d::ScopedCustomShader2D Blur::start() const
    {
        return m_rgbShiftShader.start();
    }
}
