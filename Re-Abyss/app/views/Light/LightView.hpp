#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/PixelShader.hpp>
#include <abyss/commons/Fwd.hpp>

#include "LightVM.hpp"
namespace abyss
{
    class LightShader;

    class LightView
    {
    private:
        s3d::RenderTexture m_rt;
        s3d::Array<LightVM> m_rights;
        std::shared_ptr<LightShader> m_shader;
    public:
        LightView();

        void clear();
        void push(const LightVM& light);
        void draw(const s3d::Texture& dest, double time) const;
    };
}