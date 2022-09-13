#pragma once
#include <abyss/views/Shader/Color/ColorShader.hpp>

namespace abyss::Sfx
{
    class ColorLayer
    {
    public:
        ColorLayer();
        ColorLayer& setColor(const s3d::ColorF& color);
        ColorLayer& setIsValid(bool isValid)
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
        ColorShader m_shader;
        bool m_isValid;
    };
}
