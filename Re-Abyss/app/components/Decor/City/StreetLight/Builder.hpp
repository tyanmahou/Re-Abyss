#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Decor::City
{
    struct  StreetLightEntity;
}

namespace abyss::Decor::City::StreetLight
{
    struct Builder
    {
        static void Build(DecorObj* pObj, const StreetLightEntity& entity);
    };
}