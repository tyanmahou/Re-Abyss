#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    /// <summary>
    /// 光源
    /// </summary>
    class LightModel
    {
    private:
        s3d::Vec2 m_pos;
        double m_range;
        double m_brightness;
    public:
        LightModel() = default;
        LightModel(const s3d::Vec2& pos, double range, double brightness = 1.0);

        inline const s3d::Vec2& getPos()const { return m_pos; }
        inline double getRange() const { return m_range; }
        inline double getBrightness() const { return m_brightness; }

    };
}