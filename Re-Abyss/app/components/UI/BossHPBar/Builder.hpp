#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
{
    class DamageCtrl;
}
namespace abyss::UI::BossHPBar
{
    struct Builder
    {
        static void Build(UIObj* pUi, Actor::ActorObj* pActor);
        static void Build(UIObj* pUi, Ref<Actor::HP> hp, Ref<Actor::DamageCtrl> damage = nullptr);
    };
}
