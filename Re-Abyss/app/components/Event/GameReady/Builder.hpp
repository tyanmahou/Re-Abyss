#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss::Event::GameReady
{
    struct Builder
    {
        static void Build(IEvent* pEvent);
    };
}