#pragma once
#include <Siv3D/Font.hpp>
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Novel/TagString.hpp>

namespace abyss::Novel
{
    class TagStringView
    {
    public:
        static void Draw(
            const s3d::Font& font,
            const TagString& text,
            const s3d::Vec2& basePos,
            double time,
            double alpha = 1.0
        );
        static void DrawPrev(
            const s3d::Font& font,
            const TagString& text,
            const s3d::Vec2& basePos,
            double time,
            double alpha = 1.0
        );
    };
}