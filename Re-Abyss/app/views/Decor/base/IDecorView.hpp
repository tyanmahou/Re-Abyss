#pragma once
#include <Siv3D/Rectangle.hpp>

namespace abyss
{
    class IDecorView
    {
    public:
        virtual bool isInScreen(const s3d::RectF& screen) = 0;
        virtual void draw() const = 0;
    };
}