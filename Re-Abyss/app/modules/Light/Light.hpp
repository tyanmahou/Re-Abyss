#pragma once
#include <abyss/modules/Light/LightColor.hpp>
#include <abyss/views/Light/LightView.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/ScopedCustomShader2D.hpp>

namespace abyss
{
    class Light
    {
    public:
        void clear();

        void addCircle(const s3d::Vec2& pos, double radius, double brightness = 1.0);
        void addPie(const s3d::Vec2& pos, double radius, double startAngle, double angle, double brightness = 1.0);
        void addArc(const s3d::Vec2& pos, double radius, double innerAntiRadius, double angle, double endAngle, double brightness = 1.0);

        void addShadow(std::function<void(double)> shadowDraw);

        void update(double dt);
        void render() const;

        Light& initColor(const s3d::Optional<s3d::ColorF>& color)
        {
            m_color.initColor(color);
            return *this;
        }

        Light& setNextColor(const s3d::Optional<s3d::ColorF>& color)
        {
            m_color.setNextColor(color);
            return *this;
        }

        Light& setDefaultColor(const s3d::ColorF& color)
        {
            m_color.setDefaultColor(color);
            return *this;
        }

        const s3d::ColorF& getColor() const;
        s3d::ScopedCustomShader2D start() const;

    private:
        double m_time = 0.0;
        LightView m_view;
        LightColor m_color;
    };
}