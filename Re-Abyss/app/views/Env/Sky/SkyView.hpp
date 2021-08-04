#pragma once
#include "SkyShader.hpp"
#include <abyss/commons/Fwd.hpp>
namespace abyss::Env
{
    class SkyView
    {
        SkyShader m_skyShader;
        s3d::Texture m_texture;
        s3d::Texture m_texture2;
    public:
        SkyView();

        SkyView& setTime(double time);

        void draw(const s3d::Vec2& pos) const;
    };
}