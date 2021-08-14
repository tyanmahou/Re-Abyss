#pragma once
#include <Siv3D/Types.hpp>

namespace abyss
{
    enum class CameraTargetPriority : s3d::int32
    {
        Lowest = -999,
        Normal = 0,
        Player = 1,
        Move = 2,
    };
}