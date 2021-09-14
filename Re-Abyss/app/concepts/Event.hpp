#pragma once
#include <type_traits>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    template<class Type, class... Args>
    concept EventBuildy = requires(Event::EventObj * pEvent, Args&&... args)
    {
        Type::Build(pEvent, std::forward<Args>(args)...);
    };
}