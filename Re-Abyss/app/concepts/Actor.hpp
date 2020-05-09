#pragma once
#include <type_traits>
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss
{
    /// <summary>
    /// アクターか
    /// </summary>
    template<class Type>
    concept IsActor = std::is_base_of_v<IActor, Type>;
}