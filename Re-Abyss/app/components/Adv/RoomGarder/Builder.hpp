#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Adv::RoomGarder
{
    struct Builder
    {
        [[REFLECTION(Setup)]]
        static void Setup(AdvObj* pTalk);

        class Appear
        {
            [[REFLECTION(Start)]]
            static void Start(AdvObj* pTalk);
            [[REFLECTION(End)]]
            static void End(AdvObj* pTalk);
        };

        class Disappear
        {
            [[REFLECTION(Start)]]
            static void Start(AdvObj* pTalk);
            [[REFLECTION(End)]]
            static void End(AdvObj* pTalk);
        };

        [[REFLECTION(Teardown)]]
        static void Teardown(AdvObj* pTalk);
    };
}
