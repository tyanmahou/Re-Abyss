#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/scenes/Data/SequecneData.hpp>
#include <Emaject.hpp>

namespace abyss::Factory::System
{
#if ABYSS_DEVELOP
    emaject::Injector DevPortal(SequecneData* pData);
#endif
    emaject::Injector Splash(SequecneData* pData);
    emaject::Injector Title(SequecneData* pData);
    emaject::Injector SaveSelect(SequecneData* pData);
    emaject::Injector Home(SequecneData* pData);
    emaject::Injector StageResult(SequecneData* pData);
}
