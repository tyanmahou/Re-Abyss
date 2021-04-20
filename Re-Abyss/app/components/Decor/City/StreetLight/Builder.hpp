#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::decor::City
{
    struct  StreetLightEntity;
}

namespace abyss::decor::City::StreetLight
{
    struct Builder
    {
        static void Build(DecorObj* pObj, const StreetLightEntity& entity);
    };
}