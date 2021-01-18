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

    inline s3d::String Name(UserPlayMode value)
    {
        if (value == UserPlayMode::Normal) {
            return U"ノーマルモード";
        }
        if (value == UserPlayMode::Hard) {
            return U"ハードモード";
        }
    }
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
            return UserPlayMode::Normal;
        }

        s3d::String operator()(UserPlayMode value)
        {
            if (value == UserPlayMode::Normal) {
                return U"Normal";
            }
            if (value == UserPlayMode::Hard) {
                return U"Hard";
            }
            return U"Normal";
        }
    };
}