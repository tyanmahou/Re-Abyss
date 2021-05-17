#include "LightVM.hpp"
#include <Siv3D.hpp>

namespace abyss::Decor::City::StreetLight
{
    void LightVM::draw() const
    {
        ScopedRenderStates2D blend(BlendState::Additive);
        double a = 0.3 + 0.2 * Periodic::Triangle0_1(2.0s, m_time);
        s3d::ColorF innerColor{ 0.8, 0.8, 1.0 , a };
        constexpr s3d::ColorF outerColor{ 0.5, 0.5, 0.0 , 0 };

        const auto radius = Periodic::Triangle0_1(0.5s, m_time) * 1.0 + m_radius;
        Circle(m_pos, radius).draw(innerColor, outerColor);

        const double innerRadius = 40.0;
        const auto offs = Vec2{ 10, -10 } - Vec2{ 0, -1 }.rotate(Math::ToRadians(185.0 + 15.0)) * innerRadius;
        Circle(m_pos + offs, m_radius * 7.0).drawArc(
            Math::ToRadians(185.0),
            Math::ToRadians(30.0),
            m_radius * 7.0 - innerRadius,
            0,
            innerColor.setA(innerColor.a * 0.8),
            outerColor
        );
    }
}