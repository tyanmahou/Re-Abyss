#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/RenderTexture.hpp>
#include <Siv3D/Transformer2D.hpp>

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
        void render(double time) const;
        s3d::ScopedCustomShader2D start(const s3d::ColorF& color) const;
    };
}