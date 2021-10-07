#include "DistUtl.hpp"
#include <abyss/views/util/VertexUtil/VertexUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::DistUtil
{
    void Draw(const s3d::Circle& circle, double innerPower, double outerPower)
    {
        auto callback = [](s3d::Vertex2D* pVertex, float c, float s) {
            Float2 dir = (Float2{ c, s }.normalized() + Float2(1.0f, 1.0f)) / 2.0f;
            pVertex->color.set(dir.x, dir.y, 0, 0.5f);
        };
        auto colorMap = [=](s3d::Vertex2D* pVertex, s3d::Vertex2D::IndexType vertexSize) {
            (pVertex++)->color = Float4(0.5f, 0.5f, static_cast<float>(innerPower) / 128.0f, 0.5f);

            for (size_t i = 1; i < vertexSize; ++i) {
                (pVertex++)->color.z = static_cast<float>(outerPower) / 128.0f;
            }
        };
        VertexUtil::DrawCircle(circle, callback, colorMap);
    }
    void Draw(const s3d::Circle & circle, double power)
    {
        Draw(circle, power, power);
    }
    void DrawFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double innerPower, double outerPower)
    {
        auto callback = [=](s3d::Vertex2D* outer, s3d::Vertex2D* inner, float c, float s) {
            Float2 dir = (Float2{ c, s }.normalized() + Float2(1.0f, 1.0f)) / 2.0f;
            outer->color.set(dir.x, dir.y, static_cast<float>(outerPower) / 128.0f, 0.5f);
            inner->color.set(dir.x, dir.y, static_cast<float>(innerPower) / 128.0f, 0.5f);
        };
        VertexUtil::DrawCircleFrame(
            circle,
            innerThickness,
            outerThickness,
            callback,
            nullptr
        );
    }
    void DrawFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double power)
    {
        DrawFrame(circle, innerThickness, outerThickness, power, power);
    }
    void DrawFrame(const s3d::Circle & circle, double thickness, double power)
    {
        DrawFrame(circle, thickness * 0.5, thickness * 0.5, power);
    }
}
