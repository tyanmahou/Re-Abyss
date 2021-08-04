#pragma once
#include <Siv3D/Texture.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Env
{
    class WaterSarfaceView
    {
        s3d::Texture m_texture;
        double m_time;
    public:
        WaterSarfaceView();

        WaterSarfaceView& setTime(double time);

        void drawBack(const CameraView& camera) const;
        void drawFront(const CameraView& camera) const;
    };
}