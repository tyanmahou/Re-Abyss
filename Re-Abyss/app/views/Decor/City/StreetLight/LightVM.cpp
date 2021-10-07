#include "LightVM.hpp"
#include <Siv3D.hpp>
#include <abyss/views/util/VertexUtil/VertexUtil.hpp>

namespace abyss::Decor::City::StreetLight
{
    void LightVM::draw() const
    {
        ScopedRenderStates2D blend(BlendState::Additive);
        double a = 0.4 + 0.1 * Periodic::Triangle0_1(2.0s, m_time);
        s3d::ColorF innerColor{ 0.8, 0.8, 1.0 , a };
        constexpr s3d::ColorF outerColor{ 0.5, 0.5, 0.0 , 0 };

        const auto radius = Periodic::Triangle0_1(0.5s, m_time) * 1.0 + m_radius;
        Circle(m_pos, radius).draw(innerColor, outerColor);

        const double innerRadius = 40.0;
        const auto offs = Vec2{ 10, -10 } - Vec2{ 0, -1 }.rotate(Math::ToRadians(185.0 + 15.0)) * innerRadius;
        innerColor.setA(innerColor.a * 0.8);

        auto colorMap = [=](s3d::Vertex2D* pVertex, s3d::Vertex2D::IndexType size) {
            auto inner = innerColor.toFloat4();
            auto outer = outerColor.toFloat4();
            for (size_t i = 0; i < size / 2; ++i) {
                (pVertex++)->color = outer;
                auto tri = Periodic::Jump0_1(static_cast<double>(size), static_cast<double>(i * 2 + 1));
                (pVertex++)->color = inner * static_cast<float>(tri);
            }
        };
        VertexUtil::DrawCircleArc(
            Circle(m_pos + offs, m_radius * 6.0),
            185_deg,
            30_deg,
            m_radius * 6.0 - innerRadius,
            0,
            nullptr,
            std::move(colorMap)
        );
    }
}