#pragma once

#if ABYSS_DEBUG

namespace abyss::Debug::DebugFlag
{
    inline constexpr auto* LogIsVisible = U"Log/IsVisible";
    inline constexpr auto* LogNormal = U"Log/Normal";
    inline constexpr auto* LogWarn = U"Log/Warn";
    inline constexpr auto* LogError = U"Log/Error";
    inline constexpr auto* LogLoad = U"Log/Load";

    inline constexpr auto* AlertEffectCount = U"Alert/EffectCount";
    inline constexpr auto* AlertDecorCount = U"Alert/DecorCount";

    inline constexpr auto* DrawCollider = U"Draw/Collider";
    inline constexpr auto* DrawMapCollider = U"Draw/MapCollider";

    inline constexpr auto* PostEffectLight = U"PostEffect/Light";
    inline constexpr auto* PostEffectDistortion = U"PostEffect/Distortion";
}

#endif