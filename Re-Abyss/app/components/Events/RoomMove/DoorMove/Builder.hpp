#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actor/Gimmick/Door/DoorModel.hpp>

namespace abyss::Event::RoomMove::DoorMove
{
    struct Builder
    {
        static void Build(
            IEvent* pEvent,
            const RoomModel& nextRoom,
            const Actor::Gimmick::Door::DoorModel& door,
            const s3d::Vec2& playerPos,
            std::function<void()> fadeInCallback,
            double milliSec = 2000.0
        );
    };
}