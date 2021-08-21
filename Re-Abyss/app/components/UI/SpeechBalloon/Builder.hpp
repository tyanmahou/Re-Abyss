#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::SpeechBalloon
{
    struct Builder
    {
        static void Build(UIObj* pUi, Actor::ActorObj* actor);
    };
}