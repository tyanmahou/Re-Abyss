#pragma once
#include <abyss/modules/DrawManager/DrawLayer.hpp>

namespace abyss::Effect::EffectLayer
{
    inline constexpr DrawLayer DecorBack = static_cast<DrawLayer>(static_cast<s3d::int32>(DrawLayer::DecorBack) - 1);
    inline constexpr DrawLayer WorldBack = static_cast<DrawLayer>(static_cast<s3d::int32>(DrawLayer::World) - 1);
    inline constexpr DrawLayer WorldFront = DrawLayer::World;
    inline constexpr DrawLayer DecorFront = DrawLayer::DecorFront;
};