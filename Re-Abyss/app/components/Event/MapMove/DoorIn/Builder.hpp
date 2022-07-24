#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Gimmick/Door/DoorData.hpp>
#include <abyss/components/Event/MapMove/LinkData.hpp>

namespace abyss::Event::MapMove::DoorIn
{
    struct Builder
    {
        static void Build(
            EventObj* pEvent,
            const LinkData& link,
            const Actor::Gimmick::Door::DoorData& door,
            const s3d::Vec2& playerPos,
            double milliSec = 1000.0
        );
    };
}
