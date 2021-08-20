#pragma once
#include "GimmickEntity.hpp"

namespace abyss::Actor::Gimmick
{
    struct BulletinEntity : GimmickEntity
    {
        s3d::FilePath event;
    };
}