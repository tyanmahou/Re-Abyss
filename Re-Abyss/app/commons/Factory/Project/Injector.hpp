#pragma once
#if ABYSS_DEVELOP
#include <Emaject.hpp>

namespace abyss::Factory::Project
{
    emaject::Injector Injector();
    void Install(emaject::Injector& injector);
}

#endif
