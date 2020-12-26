#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Event::CreateBossHPBar
{
    struct Builder
    {
        static void Build(IEvent* pEvent, const Ref<ui::IUserInterface>& hpBar);
    };
}