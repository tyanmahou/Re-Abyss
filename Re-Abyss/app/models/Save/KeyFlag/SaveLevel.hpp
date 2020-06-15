#pragma once
#include <Siv3D/Fwd.hpp>
namespace abyss
{
    enum class SaveLevel
    {
        Room, // ルーム移動してもリセットされない
        Restart, // リスタートしてもリセットされない
        Never, // リセットされない
    };
}
