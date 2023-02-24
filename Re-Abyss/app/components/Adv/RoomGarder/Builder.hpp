#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Adv::RoomGarder
{
    struct Builder
    {
        [[REFLECTION(Setup)]]
        static void Setup(AdvObj* pObj);

        class Appear
        {
            [[REFLECTION(Start)]]
            static void Start(AdvObj* pObj);
            [[REFLECTION(End)]]
            static void End(AdvObj* pObj);
        };

        class Disappear
        {
            [[REFLECTION(Start)]]
            static void Start(AdvObj* pObj);
            [[REFLECTION(End)]]
            static void End(AdvObj* pObj);
        };

        [[REFLECTION(Teardown)]]
        static void Teardown(AdvObj* pObj);
    };
}
