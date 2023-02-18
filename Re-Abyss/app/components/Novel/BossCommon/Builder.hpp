#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Novel::BossCommon
{
    struct Builder
    {
        [[REFLECTION(ShowHpBar)]]
        static void ShowHpBar(TalkObj* pTalk);
    };
}
