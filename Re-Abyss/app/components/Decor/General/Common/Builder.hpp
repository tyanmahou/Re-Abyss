#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::decor::General
{
    struct  CommonEntity;
}

namespace abyss::decor::General::Common
{
    struct Builder
    {
        static void Build(DecorObj* pObj, const CommonEntity& entity);
    };
}