#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::Home::Top
{
    class IModeThumb
    {
    public:
        virtual ~IModeThumb() = default;

        virtual void drawSelected(const s3d::Vec2& pos, double time) const = 0;
        virtual void drawUnselected(const s3d::Vec2& pos, double time) const = 0;
    };
}
