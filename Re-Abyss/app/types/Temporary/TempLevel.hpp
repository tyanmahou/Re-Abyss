#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    /// <summary>
    /// 一時保存レベル
    /// </summary>
    enum class TempLevel
    {
        /// <summary>ルーム移動でリセット</summary>
        Room,
        /// <summary>リスタートでリセット</summary>
        Restart,
        /// <summary>ステージからでてリセット</summary>
        Exit,
        /// <summary>リセットされない</summary>
        Never,
    };
}
