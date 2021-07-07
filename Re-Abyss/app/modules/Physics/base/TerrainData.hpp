#pragma once
#include <Siv3D/Rectangle.hpp>
#include <abyss/types/ColDirection.hpp>

namespace abyss::Physics
{
    struct TerrainData
    {
        s3d::RectF region;
        ColDirection col;
    };
}