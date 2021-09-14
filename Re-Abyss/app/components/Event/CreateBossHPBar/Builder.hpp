#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Event::CreateBossHPBar
{
    struct Builder
    {
        static void Build(EventObj* pEvent, const Ref<UI::UIObj>& hpBar);
    };
}