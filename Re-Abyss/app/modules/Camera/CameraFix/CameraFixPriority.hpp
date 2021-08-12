#pragma once
#include <Siv3D/Types.hpp>

namespace abyss
{
    enum class CameraFixPriority : s3d::int32
    {
        Normal = 0,
        RoomMove = 1,
    };
}