#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor
{
    class ILocator
    {
    public:
        virtual ~ILocator() = default;
        virtual s3d::Vec2 getCenterPos() const = 0;
    };
}