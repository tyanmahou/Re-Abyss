#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/scenes/Data/SequecneData.hpp>
#include <Emaject.hpp>

namespace abyss::Factory::System
{
#if ABYSS_DEVELOP
    emaject::Injector DevPortal(Manager* pManager, SequecneData* pData);
#endif
    emaject::Injector Splash(Manager* pManager);
}
