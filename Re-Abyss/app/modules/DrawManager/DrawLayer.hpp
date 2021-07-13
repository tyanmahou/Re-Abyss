#pragma once
#include <Siv3D/String.hpp>

namespace abyss
{
    /// <summary>
    /// 描画レイヤー
    /// </summary>
    enum class DrawLayer
    {
        BackGround,
        DecorBack,
        DecorMiddle,
        World,
        DecorFront,

        UI,
        Size,
        Land = DecorMiddle,

        EffectDecorBack = DecorBack - 1,
        EffectWorldBack = World - 1,
        EffectWorldFront = World,
        EffectDecorFront = DecorFront,
    };

    inline constexpr size_t DrawLayerSize = static_cast<size_t>(DrawLayer::Size);
}