#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/modules/Camera/CameraTarget/CameraTargetPriority.hpp>

namespace abyss
{
    class ICameraTarget
    {
    public:
        virtual ~ICameraTarget() = default;
        virtual s3d::Vec2 targetPos() const = 0;
        virtual CameraTargetPriorityType priority() const = 0;

        virtual bool isActive() const = 0;
        virtual bool isEnd() const = 0;
    };
}