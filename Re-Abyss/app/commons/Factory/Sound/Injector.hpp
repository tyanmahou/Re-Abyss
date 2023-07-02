#pragma once
#include <Emaject.hpp>

namespace abyss::Factory::Sound
{
    struct SoundBank
    {
        static emaject::Injector Injector();
        static void Install(emaject::Injector& injector);
    };
}
