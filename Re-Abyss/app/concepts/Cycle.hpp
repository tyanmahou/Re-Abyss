#pragma once
#include <abyss/modules/Cycle/base/CycleObj.hpp>

namespace abyss::Cycle
{
    template<class Type, class... Args>
    concept CycleBuildy = requires(CycleObj* pCycle, Args&&... args)
    {
        Type::Build(pCycle, std::forward<Args>(args)...);
    };
}