#include <abyss/modules/Sfx/DeadEffect/DeadEffect.hpp>

namespace  abyss::Sfx
{
    constexpr ColorF defaultColor(1, 0, 0, 0.8);
    DeadEffect::DeadEffect():
        m_isValid(false)
    {

        m_shader
            .setBlendMode(BlendMode::Color)
            .setColor(defaultColor)
            ;
    }
    DeadEffect& DeadEffect::setColor(const s3d::ColorF& color)
    {
        m_shader.setColor(color);
        return *this;
    }
    DeadEffect& DeadEffect::resetColor()
    {
        return setColor(defaultColor);
    }
    s3d::ScopedCustomShader2D DeadEffect::start() const
    {
        return m_shader.start();
    }
}
