#pragma once
#include <abyss/values/Forward.hpp>
#include <Siv3D/Types.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Actor::Player
{
    struct PlayerDesc
    {
        PlayerDesc();

        s3d::int32 hp;
        s3d::int32 startId;

        struct DirectInfo
        {
            s3d::Vec2 pos;
            Forward forward;
        };
        s3d::Optional<DirectInfo> direct;
    };
}
