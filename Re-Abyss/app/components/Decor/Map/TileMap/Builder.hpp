#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::decor::Map
{
    class TileMapModel;
}

namespace abyss::decor::Map::TileMap
{
    struct Builder
    {
        static void Build(DecorObj* pObj, const TileMapModel& tileMap);
    };
}