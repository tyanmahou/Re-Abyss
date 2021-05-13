#pragma once
#include "GimmickEntity.hpp"

namespace abyss::Actor::Gimmick
{
    enum class DoorKind
    {
        Common,
        Boss,
    };
    struct DoorEntity : GimmickEntity
    {
        s3d::int32 startId;
        s3d::Vec2 size;
        DoorKind kind;
    };
}