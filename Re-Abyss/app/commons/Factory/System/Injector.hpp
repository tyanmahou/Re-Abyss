#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/scenes/Data/SequecneData.hpp>
#include <Emaject.hpp>

namespace abyss::Factory::System
{
    struct StageFactoryOption;

#if ABYSS_DEVELOP
    emaject::Injector DevPortal(SequecneData* pData);
    emaject::Injector Experiment(SequecneData* pData);
#endif
    emaject::Injector Splash(SequecneData* pData);
    emaject::Injector Title(SequecneData* pData);
    emaject::Injector SaveSelect(SequecneData* pData);
    emaject::Injector Home(SequecneData* pData);
    emaject::Injector Stage(SequecneData* pData, const StageFactoryOption& option);
    emaject::Injector StageResult(SequecneData* pData);
}
