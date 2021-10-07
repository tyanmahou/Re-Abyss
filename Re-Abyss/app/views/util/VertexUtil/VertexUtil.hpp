#pragma once
#include <Siv3D/Buffer2D.hpp>

namespace abyss
{
    /// <summary>
    /// 頂点ユーティリティ
    /// </summary>
    class VertexUtil
    {
    public:
        using CircleBuildCallback = std::function<void(s3d::Vertex2D*, float c, float s)>;
        using CircleFrameBuildCallback = std::function<void(s3d::Vertex2D* outer, s3d::Vertex2D* inner, float c, float s)>;

        using VertexCallback = std::function<void(s3d::Vertex2D*, s3d::Vertex2D::IndexType)>;
    public:
        static void DrawCircle(
            const s3d::Circle& circle,
            const CircleBuildCallback& callback,
            const VertexCallback& fixCallback
        );

        static void DrawCircleFrame(
            const s3d::Circle& circle,
            double innerThickness,
            double outerThickness,
            const CircleFrameBuildCallback& callback,
            const VertexCallback& fixCallback
        );

        static void DrawCircleArc(
            const s3d::Circle& circle,
            double startAngle,
            double angle,
            double innerThickness,
            double outerThickness,
            const CircleFrameBuildCallback& callback,
            const VertexCallback& fixCallback
        );
    };
}