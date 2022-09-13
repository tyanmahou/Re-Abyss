#include <abyss/modules/Sfx/ColorLayer/ColorLayer.hpp>

namespace  abyss::Sfx
{
    ColorLayer::ColorLayer():
        m_isValid(false)
    {
    }
    ColorLayer& ColorLayer::setColor(const s3d::ColorF& color)
    {
        m_shader.setColor(color);
        return *this;
    }
    s3d::ScopedCustomShader2D ColorLayer::start() const
    {
        return m_shader.start();
    }
}
