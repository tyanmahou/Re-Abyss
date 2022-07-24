#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Gimmick/Door/DoorData.hpp>

namespace abyss::Event::MapMove::DoorIn
{
    struct Builder
    {
        static void Build(
            EventObj* pEvent,
            const Actor::Gimmick::Door::DoorData& door,
            const s3d::String& link,
            const s3d::Vec2& playerPos,
            double milliSec = 1000.0
        );
    };
}
