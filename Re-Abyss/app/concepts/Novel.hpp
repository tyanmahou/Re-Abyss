#pragma once
#include <type_traits>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    template<class Type, class... Args>
    concept TalkBuildy = requires(Novel::TalkObj * pTalk, Args&&... args)
    {
        Type::Build(pTalk, std::forward<Args>(args)...);
    };
}