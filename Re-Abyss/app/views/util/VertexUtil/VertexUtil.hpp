#pragma once
#include <Siv3D/Buffer2D.hpp>

namespace abyss
{
    class VertexUtil
    {
    public:
        static void DrawCircle(
            const s3d::Circle& circle,
            const std::function<void(s3d::Vertex2D*, float c, float s)>& callback,
            const std::function<void(s3d::Vertex2D*, s3d::Vertex2D::IndexType)>& fixCallback
        );

        static void DrawCircleFrame(
            const s3d::Circle& circle,
            double innerThickness,
            double outerThickness,
            const std::function<void(s3d::Vertex2D* outer, s3d::Vertex2D* inner, float c, float s)>& callback,
            const std::function<void(s3d::Vertex2D*, s3d::Vertex2D::IndexType)>& fixCallback
        );

        static void DrawCircleArc(
            const s3d::Circle& circle,
            double startAngle,
            double angle,
            double innerThickness,
            double outerThickness,
            const std::function<void(s3d::Vertex2D* outer, s3d::Vertex2D* inner, float c, float s)>& callback,
            const std::function<void(s3d::Vertex2D*, s3d::Vertex2D::IndexType)>& fixCallback
        );
    };
}