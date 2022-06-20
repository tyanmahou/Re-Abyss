#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss::Event::RoomMove::BasicMove
{
    struct Builder
    {
        static void Build(EventObj* pEvent, const Room::RoomData& nextRoom, double milliSec = 2000.0);
    };
}
