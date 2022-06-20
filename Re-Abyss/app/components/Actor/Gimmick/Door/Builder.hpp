#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/models/Room/RoomData.hpp>
#include <abyss/models/Actor/Gimmick/Door/DoorModel.hpp>

namespace abyss::Actor::Gimmick::Door
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const DoorModel& door, const Room::RoomData& nextRoom);
    };
}
