#pragma once
#include <abyss/utils/Coro/Generator/Generator.hpp>

namespace abyss::UI::List
{

    template<class Type>
    class IContentList
    {
    public:
        virtual ~IContentList() = default;
        virtual Coro::Generator<Type> getList() const = 0;
    };
}
