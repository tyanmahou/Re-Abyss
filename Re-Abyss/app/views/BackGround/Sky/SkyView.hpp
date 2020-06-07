#pragma once
#include "SkyShader.hpp"
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class SkyView
    {
        SkyShader m_skyShader;
        s3d::Texture m_texture;
    public:
        SkyView();

        void draw(const CameraView& camera) const;
    };
}