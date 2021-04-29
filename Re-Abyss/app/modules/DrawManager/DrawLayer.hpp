#pragma once

namespace abyss
{
    /// <summary>
    /// 描画レイヤー
    /// </summary>
    enum class DrawLayer
    {
        Size,
    };

    inline constexpr size_t DrawLayerSize = static_cast<size_t>(DrawLayer::Size);
}