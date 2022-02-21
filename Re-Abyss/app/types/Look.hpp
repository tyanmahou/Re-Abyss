#pragma once
#include <abyss/types/Forward.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    class Look
    {
    public:
        Look():
            m_value(0, 0)
        {}
        Look(double x, double y) :
            m_value(x, y)
        {}
        Look(const s3d::Vec2& v):
            m_value(v)
        {}

        bool isForward(Forward f) const
        {
            return m_value.dot(ToVec2(f)) > 0;
        }

        Forward verticalForward() const
        {
            if (m_value.y > 0) {
                return Forward::Down;
            } else if (m_value.y < 0) {
                return Forward::Up;
            }
            return Forward::None;
        }
        Forward horizonalForward() const
        {
            if (m_value.x > 0) {
                return Forward::Right;
            } else if (m_value.x < 0) {
                return Forward::Left;
            }
            return Forward::None;
        }
    private:
        s3d::Vec2 m_value;
    };
}