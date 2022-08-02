#include <abyss/modules/Sfx/DecorFar/DecorFar.hpp>

namespace abyss::Sfx
{
    void DecorFar::update(double dt)
    {
        m_time +=dt;
        m_shader.setTime(m_time);
    }
    s3d::ScopedCustomShader2D DecorFar::start() const
    {
        return m_shader.start();
    }
}
