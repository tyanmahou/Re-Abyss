#include <abyss/values/Look.hpp>

namespace abyss
{
    Look::Look() :
        m_value(0, 0)
    {}
    Look::Look(double x, double y) :
        m_value(x, y)
    {}
    Look::Look(const s3d::Vec2& v) :
        m_value(v)
    {}

    bool Look::isForward(Forward f) const
    {
        return m_value.dot(f.toVec2()) > 0;
    }
    Forward Look::verticalForward() const
    {
        if (m_value.y > 0) {
            return Forward::Down();
        } else if (m_value.y < 0) {
            return Forward::Up();
        }
        return Forward::None();
    }
    Forward Look::horizonalForward() const
    {
        if (m_value.x > 0) {
            return Forward::Right();
        } else if (m_value.x < 0) {
            return Forward::Left();
        }
        return Forward::None();
    }
}
