#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss::Event::MapMove
{
    class IMapMoveCallback
    {
    public:
        virtual ~IMapMoveCallback() = default;

        virtual void onMoveStart() = 0;
        virtual void onMoveUpdate(double t) = 0;
        virtual void onMoveEnd() = 0;

        virtual s3d::Vec2 calcCameraPos() const = 0;
        virtual s3d::Vec2 calcPlayerPos() const = 0;
    };
}
