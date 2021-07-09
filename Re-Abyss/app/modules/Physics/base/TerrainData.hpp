#pragma once
#include <memory>
#include <Siv3D/Rectangle.hpp>
#include <abyss/types/ColDirection.hpp>
#include "ITerrainExtData.hpp"
#include "Tag.hpp"

namespace abyss::Physics
{
    struct TerrainData
    {
        s3d::RectF region;
        ColDirection col;

        TagType tag;
        std::shared_ptr<ITerrainExtData> extData;
    };
}