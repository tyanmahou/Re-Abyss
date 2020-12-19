#pragma once
#include "Depends.hpp"
#include <Siv3D/HashTable.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
    class DependsSort
    {
        s3d::HashTable<IComponent*, Depends> m_depends;

    public:
        void regist(IComponent* component, Depends depends);
        s3d::Array<Ref<IComponent>> sort(const std::type_index& process, const s3d::Array<Ref<IComponent>>& origin);
    };
}