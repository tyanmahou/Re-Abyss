#pragma once

namespace abyss::Decor
{
    /// <summary>
    /// バッファレイヤー
    /// </summary>
    enum class BufferLayer
    {
        Front,
        Back,
    };

    /// <summary>
    /// バッファの反転
    /// </summary>
    /// <param name="layer"></param>
    /// <returns></returns>
    inline BufferLayer FlipBuffer(BufferLayer layer)
    {
        if (layer == BufferLayer::Back) {
            return BufferLayer::Front;
        } else {
            return BufferLayer::Back;
        }
    }
}