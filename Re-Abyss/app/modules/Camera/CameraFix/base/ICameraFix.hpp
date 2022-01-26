#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/modules/Camera/CameraFix/CameraFixPriority.hpp>

namespace abyss
{
    class ICameraFix
    {
    public:
        virtual ~ICameraFix() = default;

        virtual s3d::Vec2 apply(const s3d::Vec2& target) const = 0;

        virtual CameraFixPriority priority() const = 0;
    };
}