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
        double m_r;
        double m_brightness;
    public:
        LightModel() = default;
        LightModel(const s3d::Vec2& pos, double r, double brightness = 1.0);

        inline const s3d::Vec2& getPos()const { return m_pos; }
        inline double getR() const { return m_r; }
    };
}