#pragma once
#include <type_traits>
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss
{
    /// <summary>
    /// アクターか
    /// </summary>
    template<class Type>
    concept Actory = std::is_same_v<Actor::IActor, Type>;

    template<class Type, class... Args>
    concept ActBuildy = requires(Actor::IActor*pActor, Args&&... args)
    {
        Type::Build(pActor, std::forward<Args>(args)...);
    };
}