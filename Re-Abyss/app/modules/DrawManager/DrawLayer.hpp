#pragma once
#include <Siv3D/String.hpp>

namespace abyss
{
    /// <summary>
    /// 描画レイヤー
    /// </summary>
    enum class DrawLayer
    {
        // 背景
        BackGround,

        // 装飾後方
        DecorBack,

        // 地形
        Land,

        // ワールド後方
        WorldBack,
        // ワールド
        World,
        // ワールド前方
        WorldFront,

        // 装飾前方
        DecorFront,

        // ライトより前
        LightFront,

        // UI
        UI,

        Size,
    };

    inline constexpr size_t DrawLayerSize = static_cast<size_t>(DrawLayer::Size);

    inline DrawLayer& operator++(DrawLayer& layer)
    {
        return layer = static_cast<DrawLayer>(static_cast<s3d::int32>(layer) + 1);
    }
}