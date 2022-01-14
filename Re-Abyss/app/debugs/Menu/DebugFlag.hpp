#pragma once

#if ABYSS_DEBUG

namespace abyss::Debug::DebugFlag
{
    inline constexpr auto* LogIsVisible = U"Debug/Log/IsVisible";
    inline constexpr auto* LogNormal = U"Debug/Log/Normal";
    inline constexpr auto* LogWarn = U"Debug/Log/Warn";
    inline constexpr auto* LogError = U"Debug/Log/Error";
    inline constexpr auto* LogLoad = U"Debug/Log/Load";

    inline constexpr auto* AlertProfiler = U"Debug/Alert/Profiler";
    inline constexpr auto* AlertEffectCount = U"Debug/Alert/EffectCount";
    inline constexpr auto* AlertDecorCount = U"Debug/Alert/DecorCount";
    inline constexpr auto* AlertDrawerCount = U"Debug/Alert/DrawerCount";

    inline constexpr auto* ActorDebugInfo = U"Debug/Actor/DebugInfo";
    inline constexpr auto* ActorCollider = U"Debug/Actor/Collider";
    inline constexpr auto* ActorMapCollider = U"Debug/Actor/MapCollider";
    inline constexpr auto* ActorTestBehavior = U"Debug/Actor/TestBehavior";

    inline constexpr auto* PostEffectLight = U"Debug/PostEffect/Light";
    inline constexpr auto* PostEffectDistortion = U"Debug/PostEffect/Distortion";
    inline constexpr auto* PostEffectScanline = U"Debug/PostEffect/Scanline";
}

#endif