#pragma once
#include "Executer.hpp"
#include <Siv3D/HashTable.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::detail
{
    class ExecuteSorter
    {
        s3d::HashTable<IComponent*, Executer> m_executer;

    public:
        void regist(IComponent* component, Executer executer);
        s3d::Array<Ref<IComponent>> sort(const std::type_index& process, const s3d::Array<Ref<IComponent>>& origin);
    };
}