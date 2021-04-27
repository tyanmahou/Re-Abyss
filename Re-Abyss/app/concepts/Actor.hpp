#pragma once
#include <type_traits>
#include <abyss/modules/Actors/base/ActorObj.hpp>

namespace abyss
{
    /// <summary>
    /// アクターか
    /// </summary>
    template<class Type>
    concept Actory = std::is_same_v<Actor::ActorObj, Type>;

    template<class Type, class... Args>
    concept ActBuildy = requires(Actor::ActorObj*pActor, Args&&... args)
    {
        Type::Build(pActor, std::forward<Args>(args)...);
    };
}