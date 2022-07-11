#pragma once

#if ABYSS_DEBUG

namespace abyss::Debug::DebugFlag
{
    inline constexpr auto* LogIsVisible = U"Log/IsVisible";
    inline constexpr auto* LogNormal = U"Log/Normal";
    inline constexpr auto* LogWarn = U"Log/Warn";
    inline constexpr auto* LogError = U"Log/Error";
    inline constexpr auto* LogLoad = U"Log/Load";

    inline constexpr auto* AlertProfiler = U"Alert/Profiler";
    inline constexpr auto* AlertEffectCount = U"Alert/EffectCount";
    inline constexpr auto* AlertDecorCount = U"Alert/DecorCount";
    inline constexpr auto* AlertDrawerCount = U"Alert/DrawerCount";

    inline constexpr auto* ActorDebugInfo = U"Actor/DebugInfo";
    inline constexpr auto* ActorCollider = U"Actor/Collider";
    inline constexpr auto* ActorMapCollider = U"Actor/MapCollider";
    inline constexpr auto* ActorTestBehavior = U"Actor/TestBehavior";

    inline constexpr auto* RenderFog = U"Render/Fog";
    inline constexpr auto* RenderLight = U"Render/Light";
    inline constexpr auto* RenderDistortion = U"Render/Distortion";
    inline constexpr auto* RenderScanline = U"Render/Scanline";
}

#endif
