#pragma once
#include <abyss/params/Actor/Enemy/BabyDux/BabyDesc.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    struct BabyDuxParam
    {
        [[TOML_BIND(Convene::Baby, "Convene.Baby")]]
        struct Convene
        {
            inline static s3d::Array<BabyDux::BabyDesc> Baby;
        };
    };
}
