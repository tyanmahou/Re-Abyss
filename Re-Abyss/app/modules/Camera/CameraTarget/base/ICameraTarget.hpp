#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    class ICameraTarget
    {
    public:
        virtual ~ICameraTarget() = default;
        virtual s3d::Vec2 targetPos() const = 0;
    };
}