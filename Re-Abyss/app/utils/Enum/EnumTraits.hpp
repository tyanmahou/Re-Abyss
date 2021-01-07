#pragma once
#include <type_traits>
#include <Siv3D/String.hpp>

namespace abyss
{

    template<class T> requires std::is_enum_v<T>
    struct EnumTraits{};

    template<class T> requires std::is_enum_v<T>
    s3d::String ToStr(T value)
    {
        return EnumTraits<T>{}(value);
    }

    template<class T> requires std::is_enum_v<T>
    T Perse(const s3d::String& value)
    {
        return EnumTraits<T>{}(value);
    }
}