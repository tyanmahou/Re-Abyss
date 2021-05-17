#include "Light.hpp"

namespace abyss
{
    void Light::clear()
    {
        m_view.clear();
    }

    void Light::addCircle(const s3d::Vec2& pos, double radius, double brightness)
    {
        m_view.addCircle(pos, radius, brightness);
    }

    void Light::addPie(const s3d::Vec2& pos, double radius, double startAngle, double angle, double brightness)
    {
        m_view.addPie(pos, radius, startAngle, angle, brightness);
    }

    void Light::addArc(const s3d::Vec2& pos, double radius, double innerAntiRadius, double startAngle, double angle, double brightness)
    {
        m_view.addArc(pos, radius, innerAntiRadius, startAngle, angle, brightness);
    }

    void Light::render(double time) const
    {
        m_view.render(time);
    }

    s3d::ScopedCustomShader2D Light::start(const s3d::ColorF& color) const
    {
        return m_view.start(color);
    }
}
