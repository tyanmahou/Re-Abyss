#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss::Decor
{
    struct AnimationEntity
    {
        s3d::uint32 fromGId;
        s3d::uint32 slot;
        s3d::uint32 toGId;
        double timeMilliSec;
    };
}
