#include <abyss/modules/Sfx/DeadEffect/DeadEffect.hpp>

namespace  abyss::Sfx
{
    DeadEffect::DeadEffect():
        m_isValid(false)
    {
    }
    DeadEffect& DeadEffect::setColor(const s3d::ColorF& color)
    {
        m_shader.setColor(color);
        return *this;
    }
    s3d::ScopedCustomShader2D DeadEffect::start() const
    {
        return m_shader.start();
    }
}
