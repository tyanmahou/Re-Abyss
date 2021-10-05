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

        WorldBack = DecorMiddle,
        WorldFront = DecorFront,
    };

    inline constexpr size_t DrawLayerSize = static_cast<size_t>(DrawLayer::Size);

    inline DrawLayer& operator++(DrawLayer& layer)
    {
        return layer = static_cast<DrawLayer>(static_cast<s3d::int32>(layer) + 1);
    }
}