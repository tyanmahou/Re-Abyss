#pragma once
#include <abyss/utils/Enum/EnumTraits.hpp>

namespace abyss::Actor::Gimmick
{
    /// <summary>
    /// くさむら種類
    /// </summary>
    enum class BushKind
    {
        Left,
        Center,
        Right,
    };
}

namespace abyss::Enum
{
    template<>
    struct EnumTraits<Actor::Gimmick::BushKind>
    {
        Actor::Gimmick::BushKind operator()(const s3d::String& value)
        {
            using Actor::Gimmick::BushKind;

            if (value == U"Left" || value == U"left") {
                return BushKind::Left;
            }
            if (value == U"Center" || value == U"center") {
                return BushKind::Center;
            }
            if (value == U"Right" || value == U"right") {
                return BushKind::Right;
            }
            return BushKind::Center;
        }
    };
}