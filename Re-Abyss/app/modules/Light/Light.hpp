#pragma once
#include <abyss/views/Light/LightView.hpp>
namespace abyss
{
    class Light
    {
    private:
        LightView m_view;
    public:
        void clear();

        void addCircle(const s3d::Vec2& pos, double range, double brightness = 1.0);
        void addPie(const s3d::Vec2& pos, double range, double startAngle, double endAngle, double brightness = 1.0);

        void render(double time) const;
        s3d::ScopedCustomShader2D start(const s3d::ColorF& color) const;
    };
}