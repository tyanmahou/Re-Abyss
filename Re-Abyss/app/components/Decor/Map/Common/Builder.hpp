#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::decor::Map
{
    struct  CommonEntity;
}

namespace abyss::decor::Map::Common
{
    struct Builder
    {
        static void Build(DecorObj* pObj, const CommonEntity& entity);
    };
}