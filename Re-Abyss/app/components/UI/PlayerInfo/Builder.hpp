#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::PlayerInfo
{
    struct Builder
    {
        static void Build(UIObj* pUi, Actor::ActorObj* pActor);
    };
}