#pragma once
#include <Siv3D/String.hpp>

namespace abyss
{
    /// <summary>
    /// 描画レイヤー
    /// </summary>
    enum class DrawLayer
    {
        DecorBack,
        DecorMiddle,
        World,
        DecorFront,

        Size,
        Land = DecorMiddle,
    };

    inline constexpr size_t DrawLayerSize = static_cast<size_t>(DrawLayer::Size);
}