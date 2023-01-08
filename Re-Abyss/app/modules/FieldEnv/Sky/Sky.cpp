#include <abyss/modules/FieldEnv/Sky/Sky.hpp>

namespace abyss::FieldEnv
{
    void Sky::update(double dt)
    {
        m_time += dt;
        m_view.setTime(m_time);
    }
    void Sky::draw(const s3d::Vec2& pos) const
    {
        m_view.draw(pos);
    }
}
