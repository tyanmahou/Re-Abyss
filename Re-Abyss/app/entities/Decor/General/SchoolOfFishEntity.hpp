#pragma once
#include <abyss/entities/Decor/DecorEntity.hpp>
#include <Siv3D/Point.hpp>

namespace abyss::Decor::General
{
    struct SchoolOfFishEntity : DecorEntity
    {
        s3d::Size matrixSize{64, 8};
        double speed = 175.0;
        double heightOffset = 180.0;
        double amplitude = 40.0;
    };
}