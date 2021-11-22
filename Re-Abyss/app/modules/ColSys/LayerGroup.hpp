#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss::ColSys::LayerGroup
{
    inline constexpr s3d::uint32 Player = 0x01;
    inline constexpr s3d::uint32 Enemy = 0x02;
    inline constexpr s3d::uint32 Gimmick = 0x04;
    inline constexpr s3d::uint32 Item = 0x08;
    inline constexpr s3d::uint32 Map = 0x0f;
}