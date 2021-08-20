#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Gimmick::Bulletin
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const s3d::FilePath& path);
    };
}