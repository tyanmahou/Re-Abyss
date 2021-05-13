#pragma once
#include "GimmickEntity.hpp"

namespace abyss::Actor::Gimmick
{
    struct BgmChangerEntity : GimmickEntity
    {
        s3d::FilePath bgm;
    };
}