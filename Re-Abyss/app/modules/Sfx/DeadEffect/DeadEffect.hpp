#pragma once
#include <abyss/views/Shader/Blend/BlendShader.hpp>

namespace abyss::Sfx
{
    class DeadEffect
    {
    public:
        DeadEffect();
        DeadEffect& setColor(const s3d::ColorF& color);
        DeadEffect& resetColor();
        DeadEffect& setIsValid(bool isValid)
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
        BlendShader m_shader;
        bool m_isValid;
    };
}
