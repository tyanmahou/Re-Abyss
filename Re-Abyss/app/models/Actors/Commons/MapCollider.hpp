#pragma once
#include <abyss/types/MapColInfo.hpp>

namespace abyss
{
    class MapCollider
    {
    public:
        void onCollision(MapColInfo& col);
    };
}