#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss::Event::RoomMove::BasicMove
{
    struct Builder
    {
        static void Build(IEvent* pEvent, const RoomModel& nextRoom, double milliSec = 2000.0);
    };
}