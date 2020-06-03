#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    class LightVM
    {
    private:
        s3d::Vec2 m_pos;
        double m_range;
        double m_brightness;
    public:
        LightVM() = default;
        LightVM(const s3d::Vec2 & pos, double range, double brightness = 1.0);
        void draw(double dt) const;
    };
}