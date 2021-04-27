#pragma once
#include <type_traits>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss
{
    /// <summary>
    /// UIかどうか
    /// </summary>
    template<class Type>
    concept UserInterfacey = std::is_same_v<UI::UIObj, Type>;

    template<class Type, class... Args>
    concept UIBuildy = requires(UI::UIObj * pUi, Args&&... args)
    {
        Type::Build(pUi, std::forward<Args>(args)...);
    };
}