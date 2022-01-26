#pragma once
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>

namespace abyss::Actor::Gimmick
{
    struct BgmChangerEntity : GimmickEntity
    {
        s3d::FilePath bgm;
    };
}