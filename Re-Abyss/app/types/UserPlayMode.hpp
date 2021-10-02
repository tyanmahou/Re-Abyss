#pragma once
#include <Siv3D/String.hpp>

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
        return U"ノーマルモード";
    }
}