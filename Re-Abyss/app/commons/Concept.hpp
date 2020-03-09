#pragma once

namespace abyss
{
    template<class Type>
    concept IsActor = std::is_base_of_v<IActor, Type>;
}