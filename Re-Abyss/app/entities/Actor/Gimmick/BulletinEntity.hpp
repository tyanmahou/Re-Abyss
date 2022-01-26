#pragma once
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>

namespace abyss::Actor::Gimmick
{
    struct BulletinEntity : GimmickEntity
    {
        s3d::FilePath event;
    };
}