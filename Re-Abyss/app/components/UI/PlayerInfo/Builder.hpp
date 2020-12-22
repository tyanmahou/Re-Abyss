#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::ui::PlayerInfo
{
    struct Builder
    {
        static void Build(IUserInterface* pUi, Actor::IActor* pActor);
    };
}