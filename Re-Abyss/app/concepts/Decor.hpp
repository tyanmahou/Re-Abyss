#pragma once
#include <type_traits>
#include <abyss/modules/Decor/base/DecorObj.hpp>

namespace abyss
{
    /// <summary>
    /// 装飾か
    /// </summary>
    template<class Type>
    concept Decory = std::is_same_v<Decor::DecorObj, Type>;

    template<class Type, class... Args>
    concept DecorBuildy = requires(Decor::DecorObj* pDecor, Args&&... args)
    {
        Type::Build(pDecor, std::forward<Args>(args)...);
    };
}