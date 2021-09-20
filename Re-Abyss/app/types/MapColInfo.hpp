#pragma once
#include <Siv3D/RectF.hpp>
#include <abyss/types/ColDirection.hpp>

namespace abyss
{
    struct MapColInfo
    {
        s3d::RectF region;
        ColDirection col;
    };
}