#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss::Actor
{
    struct StatePriority
    {
        static inline constexpr s3d::int32 Normal = 0;
        static inline constexpr s3d::int32 Damage = 10;
        static inline constexpr s3d::int32 Dead = 99;
    private:
        StatePriority() = delete;
    };
}