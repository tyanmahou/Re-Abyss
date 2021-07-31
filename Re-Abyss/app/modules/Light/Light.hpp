#pragma once
#include <abyss/views/Light/LightView.hpp>
#include <Siv3D/Optional.hpp>
namespace abyss
{
    class Light
    {
    private:
        LightView m_view;

        s3d::Optional<s3d::Color> m_color;
        s3d::Color m_defaultColor;
    public:
        void clear();

        void addCircle(const s3d::Vec2& pos, double radius, double brightness = 1.0);
        void addPie(const s3d::Vec2& pos, double radius, double startAngle, double angle, double brightness = 1.0);
        void addArc(const s3d::Vec2& pos, double radius, double innerAntiRadius, double angle, double endAngle, double brightness = 1.0);

        void render(double time) const;

        Light& setColor(const s3d::Optional<s3d::Color>& color)
        {
            m_color = color;
            return *this;
        }
        Light& setDefaultColor(const s3d::Color& color)
        {
            m_defaultColor = color;
            return *this;
        }

        s3d::Color calcColor() const;
        s3d::ScopedCustomShader2D start() const;
    };
}