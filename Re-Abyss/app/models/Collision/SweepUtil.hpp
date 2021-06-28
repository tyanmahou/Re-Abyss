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
        [[nodiscard]] static CShape Sweep(const s3d::Vec2& pos, const s3d::Vec2& move);
    };
}