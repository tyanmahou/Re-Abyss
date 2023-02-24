#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Adv::BossCommon
{
    struct Builder
    {
        [[REFLECTION(ShowHpBar)]]
        static void ShowHpBar(AdvObj* pTalk);
    };
}
