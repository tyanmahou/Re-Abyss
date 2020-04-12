#pragma once
#include "GimmickEntity.hpp"

namespace abyss
{
    struct DoorEntity : GimmickEntity
    {
        s3d::int32 startId;
        s3d::Vec2 size;
    };
}