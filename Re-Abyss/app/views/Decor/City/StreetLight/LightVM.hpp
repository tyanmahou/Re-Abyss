#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss::decor::City::StreetLight
{
    class LightVM
    {
    public:
        LightVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        LightVM& setRadius(double radius)
        {
            m_radius = radius;
            return *this;
        }
        LightVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }

        void draw() const;
    private:
        s3d::Vec2 m_pos;
        double m_radius = 1.0;
        double m_time = 0;
    };
}