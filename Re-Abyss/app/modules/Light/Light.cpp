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

    void Light::update(double dt)
    {
        m_time += dt;
        m_color.update(dt);
    }

    void Light::render() const
    {
        m_view.render(m_time);
    }

    const s3d::ColorF& Light::getColor() const
    {
        return m_color.getColor();
    }

    s3d::ScopedCustomShader2D Light::start() const
    {
        return m_view.start(this->getColor());
    }
}
