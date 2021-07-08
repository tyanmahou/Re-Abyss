#pragma once
#include <memory>
#include <Siv3D/Rectangle.hpp>
#include <abyss/types/ColDirection.hpp>
#include "ITerrainExtData.hpp"

namespace abyss::Physics
{
    struct TerrainData
    {
        s3d::RectF region;
        ColDirection col;

        std::shared_ptr<ITerrainExtData> extData;
    };
}