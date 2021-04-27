#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const s3d::FilePath& path);
    };
}