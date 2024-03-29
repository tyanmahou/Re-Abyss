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

        void setTime(double time)
        {
            m_time = time;
        }
        void clear();

        void add(std::function<void(double)> lightDraw);

        void addCircle(const s3d::Vec2& pos, double radius, double brightness = 1.0);
        void addPie(const s3d::Vec2& pos, double radius, double startAngle, double angle, double brightness = 1.0);
        void addArc(const s3d::Vec2& pos, double radius, double innerAntiRadius, double startAngle, double angle, double brightness = 1.0);

        void addShadow(std::function<void(double)> shadowDraw);

        s3d::ScopedCustomShader2D start(const s3d::ColorF& color) const;
    private:
        s3d::RenderTexture m_rt;
        std::shared_ptr<LightShader> m_shader;
        double m_time = 0;
    };
}
