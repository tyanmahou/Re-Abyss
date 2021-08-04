#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::Env
{
    class WaterSurfaceView
    {
        s3d::Texture m_texture;
        double m_time;
    public:
        WaterSurfaceView();

        WaterSurfaceView& setTime(double time);

        void drawBack(const s3d::Vec2& pos) const;
        void drawFront(const s3d::Vec2& pos) const;
    };
}