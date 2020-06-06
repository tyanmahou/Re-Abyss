#pragma once
#include <Siv3D/Texture.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class WaterSarfaceView
    {
        s3d::Texture m_texture;
    public:
        WaterSarfaceView();

        void drawBack(const CameraView& camera) const;
        void drawFront(const CameraView& camera) const;
    };
}