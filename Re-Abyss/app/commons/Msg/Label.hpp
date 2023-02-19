#pragma once
#include <Siv3D/StringView.hpp>

namespace abyss::Msg
{
    /// <summary>
    /// メッセージラベル
    /// </summary>
    struct Label
    {
        constexpr Label(s3d::StringView _category, s3d::StringView _key):
            category(_category),
            key(_key)
        {
        }
        s3d::StringView category;
        s3d::StringView key;
    };
}
