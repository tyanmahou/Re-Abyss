#pragma once

#if ABYSS_DEBUG

namespace abyss::Debug::DebugFlag
{
    inline constexpr auto* DrawCollider = U"Draw/Collider";
    inline constexpr auto* DrawMapCollider = U"Draw/MapCollider";
    inline constexpr auto* LogEffectCount = U"Log/EffectCount";
    inline constexpr auto* LogDecorCount = U"Log/DecorCount";
    inline constexpr auto* PostEffectLight = U"PostEffect/Light";
    inline constexpr auto* PostEffectDistortion = U"PostEffect/Distortion";
}

#endif