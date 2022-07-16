#pragma once
#include <abyss/views/Shader/RgbShift/RgbShiftShader.hpp>

namespace abyss::Sfx
{
    class Blur
    {
    public:
        Blur& setIsValid(bool isValid)
        {
            m_isValid = isValid;
            return *this;
        }
        bool isValid() const
        {
            return m_isValid;
        }
        s3d::ScopedCustomShader2D start() const;
    private:
        RgbShiftShader m_rgbShiftShader;
        bool m_isValid = false;
    };
}
