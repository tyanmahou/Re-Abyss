#pragma once
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>
#include <Siv3D/Optional.hpp>

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
        s3d::Optional<s3d::String> link;
        s3d::Vec2 size;
        DoorKind kind;
    };
}
