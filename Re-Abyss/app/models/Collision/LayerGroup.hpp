#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss::LayerGroup
{
    inline static s3d::int32 Player = 0x01;
    inline static s3d::int32 Enemy = 0x02;
    inline static s3d::int32 Gimmick = 0x04;
    inline static s3d::int32 Item = 0x08;
    inline static s3d::int32 Map = 0x0F;
}