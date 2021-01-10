#pragma once
#include <type_traits>
#include <Siv3D/String.hpp>

namespace abyss
{

    template<class T> requires std::is_enum_v<T>
    struct EnumTraits{};

    template<class T>
    concept EnumTraity = std::is_enum_v<T> && requires(T value, const s3d::String & str)
    {
        { EnumTraits<T>{}(value) } -> std::same_as<s3d::String>;
        { EnumTraits<T>{}(str) } -> std::same_as<T>;
    };

    template<EnumTraity T>
    s3d::String ToStr(T value)
    {
        return EnumTraits<T>{}(value);
    }

    template<EnumTraity T>
    T Parse(const s3d::String& value)
    {
        return EnumTraits<T>{}(value);
    }
}