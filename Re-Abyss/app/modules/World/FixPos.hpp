#pragma once

#include <tuple>
#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/types/ColDirection.hpp>

namespace abyss
{
    class FixPos
    {
        using Result = std::pair<s3d::Vec2, ColDirection>;
    private:
        FixPos() = default;
    public:
        static Result ByLatestPos(const s3d::RectF& from, const s3d::RectF& come, ColDirection col);
        static Result ByPrevPos(const s3d::RectF& from, const s3d::RectF& come, const s3d::RectF& prevCome, ColDirection col);

        static Result InnerByLatestPos(const s3d::RectF& from, const s3d::Vec2& come, ColDirection col);
    };
}