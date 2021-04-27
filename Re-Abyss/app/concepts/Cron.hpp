#pragma once
#include <type_traits>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Cron
{
    template<class Type, class... Args>
    concept BatchBuildy = requires(Batch * pBatch, Args&&... args)
    {
        Type::Build(pBatch, std::forward<Args>(args)...);
    };
}
