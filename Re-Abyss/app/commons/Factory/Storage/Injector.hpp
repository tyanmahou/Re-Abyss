#pragma once
#include <Emaject.hpp>

namespace abyss::Factory::Storage
{
    emaject::Injector Injector();
    void Install(emaject::Injector& injector);
}
