#pragma once
#include <Siv3D/String.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>

namespace abyss
{
    /// <summary>
    /// 難易度
    /// </summary>
    enum class UserPlayMode
    {
        /// <summary>通常</summary>
        Normal,

        /// <summary>ハード</summary>
        Hard,
    };
}

namespace abyss::Enum
{
    template<>
    struct EnumTraits<UserPlayMode>
    {
        UserPlayMode operator()(const s3d::String& value)
        {
            if (value == U"Normal") {
                return UserPlayMode::Normal;
            }
            if (value == U"Hard") {
                return UserPlayMode::Hard;
            }
        }

        s3d::String operator()(UserPlayMode value)
        {
            if (value == UserPlayMode::Normal) {
                return U"Normal";
            }
            if (value == UserPlayMode::Hard) {
                return U"Hard";
            }
        }
    };
}