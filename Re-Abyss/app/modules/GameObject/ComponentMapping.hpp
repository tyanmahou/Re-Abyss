#pragma once
#include <typeindex>
#include <Siv3D/Array.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/concepts/Component.hpp>

namespace abyss
{
    namespace detail
    {
        template<class T>
        struct ComponentMapping
        {
            void mapping(s3d::Array<std::type_index>& out)
            {
                out.push_back(typeid(T));
                if constexpr (HasBaseComponent<T>) {
                    ComponentMapping<typename ComponentTree<T>::Base>{}.mapping(out);
                }
            }
        };

        template<class ...Args>
        struct ComponentMapping<MultiComponents<Args...>>
        {
            void mapping(s3d::Array<std::type_index>& out)
            {
                (ComponentMapping<Args>{}.mapping(out), ...);
            }
        };
    }
    template<class Type>
    s3d::Array<std::type_index> CompoentMappingIdexes()
    {
        s3d::Array<std::type_index> result;
        detail::ComponentMapping<Type>{}.mapping(result);
        return result.sort_and_unique();
    }
}