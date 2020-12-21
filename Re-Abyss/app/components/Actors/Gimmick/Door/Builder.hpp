#pragma once
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/models/Actors/Gimmick/Door/DoorModel.hpp>

namespace abyss::Actor::Gimmick::Door
{
    struct Builder
    {
        static void Build(IActor* pActor, const DoorModel& door, const RoomModel& nextRoom);
    };
}