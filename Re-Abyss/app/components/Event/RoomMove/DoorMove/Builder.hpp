#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Gimmick/Door/DoorData.hpp>

namespace abyss::Event::RoomMove::DoorMove
{
    struct Builder
    {
        static void Build(
            EventObj* pEvent,
            const Room::RoomData& nextRoom,
            const Actor::Gimmick::Door::DoorData& door,
            const s3d::Vec2& playerPos,
            std::function<void()> fadeInCallback,
            double milliSec = 2000.0
        );
    };
}
