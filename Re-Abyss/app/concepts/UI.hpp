#pragma once
#include <type_traits>
#include <abyss/modules/UI/base/IUserInterface.hpp>

namespace abyss
{
    /// <summary>
    /// UIかどうか
    /// </summary>
    template<class Type>
    concept UserInterfacey = std::is_same_v<ui::IUserInterface, Type>;

    template<class Type, class... Args>
    concept UIBuildy = requires(ui::IUserInterface * pUi, Args&&... args)
    {
        Type::Build(pUi, std::forward<Args>(args)...);
    };
}