#pragma once
#include <Siv3D/Rectangle.hpp>

namespace abyss
{
    class IDecorVM
    {
    public:
        virtual void draw(const s3d::RectF& screen) const = 0;
    };
}