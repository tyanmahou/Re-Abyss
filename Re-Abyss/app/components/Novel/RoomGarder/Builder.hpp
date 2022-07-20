#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Novel::RoomGarder
{
    struct Builder
    {
        [[REFLECTION(Setup)]]
        static void Setup(TalkObj* pTalk);

        class Appear
        {
            [[REFLECTION(Start)]]
            static void Start(TalkObj* pTalk);
            [[REFLECTION(End)]]
            static void End(TalkObj* pTalk);
        };

        class Disappear
        {
            [[REFLECTION(Start)]]
            static void Start(TalkObj* pTalk);
            [[REFLECTION(End)]]
            static void End(TalkObj* pTalk);
        };

        [[REFLECTION(Teardown)]]
        static void Teardown(TalkObj* pTalk);
    };
}
