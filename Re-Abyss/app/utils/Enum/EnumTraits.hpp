#pragma once
#include <type_traits>
#include <Siv3D/String.hpp>

namespace abyss::Enum
{

    template<class T> requires std::is_enum_v<T>
    struct EnumTraits{};

    template<class T>
    concept Parsable = std::is_enum_v<T> && requires(T value, const s3d::String & str)
    {
        { EnumTraits<T>{}(value) } -> std::same_as<s3d::String>;
        { EnumTraits<T>{}(str) } -> std::same_as<T>;
    };

    template<Parsable T>
    s3d::String ToStr(T value)
    {
        return EnumTraits<T>{}(value);
    }

    template<Parsable T>
    T Parse(const s3d::String& value)
    {
        return EnumTraits<T>{}(value);
    }
}