#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    struct DecorAnimationEntity
    {
        s3d::uint32 fromGId;
        s3d::uint32 slot;
        s3d::uint32 toGId;
        double timeMilliSec;
    };
}