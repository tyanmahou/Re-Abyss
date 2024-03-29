#include <abyss/views/Light/LightUtil.hpp>
#include <abyss/views/util/VertexUtil/VertexUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::LightUtil
{
    void DrawCircleLight(const s3d::Vec2& pos, double radius, double brightness, double time)
    {
        const double sin0_1 = s3d::Periodic::Sine0_1(2.0s, time);
        const double alpha = s3d::Saturate(brightness * (0.9 + sin0_1 * 0.1));
        const double r = radius + 1.0 * sin0_1;
        const double maxAlphaR = r / 4.0;
        Circle(pos, maxAlphaR)
            .drawShadow(Vec2::Zero(), r - maxAlphaR, maxAlphaR, ColorF(1.0, alpha));

    }

    void DrawPieLight(const s3d::Vec2& pos, double radius, double startAngle, double angle, double brightness, double time)
    {
        const double sin0_1 = s3d::Periodic::Sine0_1(2.0s, time);
        const double alpha = s3d::Saturate(brightness * (0.9 + sin0_1 * 0.1));
        const double r = radius + 1.0 * sin0_1;

        const double offsetRad = s3d::Math::ToRadians(sin0_1 * 0.5);
        const double fixedStart = startAngle - offsetRad;
        const double fixedAngle = angle + offsetRad * 2.0;
        Circle(pos, r).drawPie(
            fixedStart,
            fixedAngle,
            ColorF(1.0, alpha),
            ColorF(1.0, 0.0)
        );
    }
    void DrawArcLight(const s3d::Vec2& pos, double radius, double innerAntiRadius, double startAngle, double angle, double brightness, double time)
    {
        const double sin0_1 = s3d::Periodic::Sine0_1(2.0s, time);
        const double alpha = s3d::Saturate(brightness * (0.9 + sin0_1 * 0.1));
        const double r = radius + 1.0 * sin0_1;

        const double offsetRad = s3d::Math::ToRadians(sin0_1 * 0.5);
        const double fixedStart = startAngle - offsetRad;
        const double fixedAngle = angle + offsetRad * 2.0;
        const auto offs = -Vec2{ 0, -1 }.rotate(fixedStart + fixedAngle / 2.0) * innerAntiRadius;

        auto colorMap = [=](s3d::Vertex2D* pVertex, s3d::Vertex2D::IndexType size) {
            auto outerColor = ColorF(1.0, 0.0).toFloat4();
            auto innerColor = ColorF(1.0, alpha).toFloat4();
            for (size_t i = 0; i < size / 2; ++i) {
                (pVertex++)->color = outerColor;
                auto tri = Periodic::Jump0_1(static_cast<double>(size), static_cast<double>(i * 2 + 1));
                (pVertex++)->color = innerColor * static_cast<float>(tri);
            }
        };
        VertexUtil::DrawCircleArc(
            Circle(pos + offs, r),
            fixedStart,
            fixedAngle,
            r - innerAntiRadius,
            0,
            nullptr,
            std::move(colorMap)
        );
    }
}
