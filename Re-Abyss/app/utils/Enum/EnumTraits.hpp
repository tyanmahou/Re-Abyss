#pragma once
#include <type_traits>
#include <Siv3D/String.hpp>

namespace abyss::Enum
{

    template<class T> requires std::is_enum_v<T>
    struct EnumTraits{};

    template<class T>
    concept ParsableToStr = std::is_enum_v<T> && requires(T value)
    {
        { EnumTraits<T>{}(value) } -> std::same_as<s3d::String>;
    };

    template<class T>
    concept ParsableFromStr = std::is_enum_v<T> && requires(const s3d::String & str)
    {
        { EnumTraits<T>{}(str) } -> std::same_as<T>;
    };

    template<class T>
    concept Parsable = ParsableToStr<T> && ParsableFromStr<T>;

    template<ParsableToStr T>
    s3d::String ToStr(T value)
    {
        return EnumTraits<T>{}(value);
    }

    template<ParsableFromStr T>
    T Parse(const s3d::String& value)
    {
        return EnumTraits<T>{}(value);
    }
}