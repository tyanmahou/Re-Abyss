#pragma once
#include <Siv3D/String.hpp>
namespace abyss::Msg
{
    /// <summary>
    /// メッセージラベル
    /// </summary>
    struct Label
    {
        s3d::String category;
        s3d::String key;
    };
}
