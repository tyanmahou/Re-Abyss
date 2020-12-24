#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss::Event::GameRestart
{
    struct Builder
    {
        static void Build(IEvent* pEvent);
    };
}