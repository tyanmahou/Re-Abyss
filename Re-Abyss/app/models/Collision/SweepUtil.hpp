#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class SweepUtil
    {
    private:
        SweepUtil() = default;
    public:
        [[nodiscard]] static CShape Sweep(const s3d::RectF& rect, const s3d::Vec2& move);
        [[nodiscard]] static CShape Sweep(const s3d::Circle& circle, const s3d::Vec2& move);
        [[nodiscard]] static CShape Sweep(const s3d::Quad& quad, const s3d::Vec2& move);
        [[nodiscard]] static CShape Sweep(const s3d::Vec2& pos, const s3d::Vec2& move);
        [[nodiscard]] static CShape Sweep(const s3d::Line& line, const s3d::Vec2& move);
        [[nodiscard]] static CShape Sweep(const s3d::Triangle& triangle, const s3d::Vec2& move);
    };
}