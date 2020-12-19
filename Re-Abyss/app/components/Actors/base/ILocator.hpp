#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor
{
    class ILocator
    {
    public:
        virtual ~ILocator() = default;
        virtual const s3d::Vec2& getPos() const = 0;
    };
}