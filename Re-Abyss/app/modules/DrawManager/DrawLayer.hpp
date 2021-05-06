#pragma once
#include <Siv3D/String.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>

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

namespace abyss::Enum
{
    template<>
    struct EnumTraits<DrawLayer>
    {
        DrawLayer operator()(const s3d::String& value)
        {
            if (value == U"decor_back") {
                return DrawLayer::DecorBack;
            }
            if (value == U"decor_middle" || value == U"land") {
                return DrawLayer::DecorMiddle;
            }
            if (value == U"world") {
                return DrawLayer::World;
            }
            if (value == U"decor_front") {
                return DrawLayer::DecorFront;
            }
            return DrawLayer::World;
        }
    };
}