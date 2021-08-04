#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::Env
{
    class WaterSarfaceView
    {
        s3d::Texture m_texture;
        double m_time;
    public:
        WaterSarfaceView();

        WaterSarfaceView& setTime(double time);

        void drawBack(const s3d::Vec2& pos) const;
        void drawFront(const s3d::Vec2& pos) const;
    };
}