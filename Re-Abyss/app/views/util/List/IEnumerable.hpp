#pragma once
#include <abyss/utils/Coro/Generator/Generator.hpp>

namespace abyss::UI::List
{

    template<class Type>
    class IEnumerable
    {
    public:
        virtual ~IEnumerable() = default;
        virtual Coro::Generator<Type> getList() const = 0;
    };
}
