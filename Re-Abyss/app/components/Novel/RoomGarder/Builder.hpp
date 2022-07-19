#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Novel::RoomGarder
{
    struct Builder
    {
        [[REFLECTION(Setup)]]
        static void Setup(TalkObj* pTalk);

        [[REFLECTION(Teardown)]]
        static void Teardown(TalkObj* pTalk);
    };
}
