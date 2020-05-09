#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
namespace abyss
{
    /// <summary>
    /// コンポーネントか
    /// </summary>
    template<class T>
    concept IsComponent = std::is_base_of_v<IComponent, T>;

    template <class T>
    concept HasBaseComponent = requires(T a)
    {
        typename ComponentTree<T>::Base;
    };
}