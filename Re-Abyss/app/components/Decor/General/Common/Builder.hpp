#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Decor::General
{
    struct  CommonEntity;
}

namespace abyss::Decor::General::Common
{
    struct Builder
    {
        static void Build(DecorObj* pObj, const CommonEntity& entity);
    };
}