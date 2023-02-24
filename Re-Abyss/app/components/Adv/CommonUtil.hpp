#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Adv
{
    class CommonUtil
    {
    public:
        [[REFLECTION(IsEventEnd)]]
        static bool IsEventEnd(AdvObj* pTalk);
    };
}
