#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Novel
{
    class NovelUtil
    {
    public:
        [[REFLECTION(IsEventEnd)]]
        static bool IsEventEnd(TalkObj* pTalk);
    };
}
