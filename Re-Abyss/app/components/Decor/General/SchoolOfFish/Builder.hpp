#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Decor::General
{
    struct SchoolOfFishEntity;
}

namespace abyss::Decor::General::SchoolOfFish
{
    struct Builder
    {
        static void Build(DecorObj* pObj, const SchoolOfFishEntity& entity);
    };
}