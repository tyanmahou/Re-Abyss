#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Decor::Map
{
    class TileMapData;
}

namespace abyss::Decor::Map::TileMap
{
    struct Builder
    {
        static void Build(DecorObj* pObj, const TileMapData& tileMap);
    };
}
