#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/RenderTexture.hpp>
#include <Siv3D/Transformer2D.hpp>

#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class LightShader;

    class LightView
    {
    public:
        LightView();

        void clear();

        void addCircle(const s3d::Vec2& pos, double range, double brightness = 1.0);

        void render(double time) const;
        s3d::ScopedCustomShader2D start(const s3d::ColorF& color) const;
    private:
        s3d::RenderTexture m_rt;
        std::shared_ptr<LightShader> m_shader;
        s3d::Array<std::function<void(double)>> m_lights;
    };
}