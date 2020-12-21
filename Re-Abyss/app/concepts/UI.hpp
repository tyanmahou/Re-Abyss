#pragma once
#include <type_traits>
#include <abyss/modules/UI/base/IUserInterface.hpp>

namespace abyss
{
    /// <summary>
    /// UIかどうか
    /// </summary>
    template<class Type>
    concept IsUserInterface = std::is_base_of_v<ui::IUserInterface, Type>;
}