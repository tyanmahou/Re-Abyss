#pragma once

#if ABYSS_DEBUG

namespace abyss::Debug::DebugFlag
{
    inline constexpr auto* LogIsVisible = U"Debug/Log/IsVisible";
    inline constexpr auto* LogNormal = U"Debug/Log/Normal";
    inline constexpr auto* LogWarn = U"Debug/Log/Warn";
    inline constexpr auto* LogError = U"Debug/Log/Error";
    inline constexpr auto* LogLoad = U"Debug/Log/Load";

    inline constexpr auto* AlertEffectCount = U"Debug/Alert/EffectCount";
    inline constexpr auto* AlertDecorCount = U"Debug/Alert/DecorCount";

    inline constexpr auto* DrawCollider = U"Debug/Draw/Collider";
    inline constexpr auto* DrawMapCollider = U"Debug/Draw/MapCollider";

    inline constexpr auto* PostEffectLight = U"Debug/PostEffect/Light";
    inline constexpr auto* PostEffectDistortion = U"Debug/PostEffect/Distortion";
}

#endif