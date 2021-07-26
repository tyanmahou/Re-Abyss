#pragma once
#include <Siv3D/Types.hpp>

namespace abyss
{
    using CameraTargetPriorityType = s3d::int32;

    namespace CameraTargetPriority
    {
        inline constexpr CameraTargetPriorityType Lowest{ -999 };
        inline constexpr CameraTargetPriorityType Normal{ 0 };
        inline constexpr CameraTargetPriorityType Player{ 1 };
        inline constexpr CameraTargetPriorityType Move{ 2 };
    }
}