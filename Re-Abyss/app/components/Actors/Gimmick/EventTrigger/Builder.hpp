#pragma once
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    struct Builder
    {
        static void Build(IActor* pActor, const s3d::FilePath& path);
    };
}