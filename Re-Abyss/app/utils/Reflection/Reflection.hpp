#pragma once
#define MKANTA_CHARTYPE char32_t
#include <mkanta.hpp>

namespace abyss
{
    template<class Type>
    using Reflect = mkanta::reflect<Type>;
}