#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Decor::Map
{
    class TileMapModel;
}

namespace abyss::Decor::Map::TileMap
{
    struct Builder
    {
        static void Build(DecorObj* pObj, const TileMapModel& tileMap);
    };
}