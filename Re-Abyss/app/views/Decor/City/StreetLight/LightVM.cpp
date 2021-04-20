#include "LightVM.hpp"
#include <Siv3D.hpp>

namespace abyss::decor::City::StreetLight
{
    void LightVM::draw() const
    {
        ScopedRenderStates2D blend(BlendState::Additive);
        double a = 0.3 + 0.2 * Periodic::Triangle0_1(2.0s, m_time);
        s3d::ColorF innerColor{ 0.8, 0.8, 1.0 , a};
        constexpr s3d::ColorF outerColor{ 0.5, 0.5, 0.0 , 0};
        Circle(m_pos, Periodic::Triangle0_1(0.5s, m_time) * 1.0 + m_radius).draw(innerColor, outerColor);
    }
}