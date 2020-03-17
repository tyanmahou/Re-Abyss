#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/RenderTexture.hpp>
#include "LightVM.hpp"

namespace abyss
{
    class LightView
    {
    private:
        s3d::RenderTexture m_rt;

        s3d::Array<LightVM> m_rights;
    public:
        void clear();
        void push(const LightVM& light);
        void draw(const s3d::Vec2& pos) const;
    };
}