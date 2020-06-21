#pragma once

#if ABYSS_DEBUG
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <abyss/utils/Singleton.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Debug
{
    class DebugManager : protected Singleton<DebugManager>
    { 
        friend class Singleton<DebugManager>;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;

        DebugManager();
    public:
        static void Update();
        static bool IsDrawColider();
        static bool IsDrawMapColider();
        static bool DisableDarkNess();

        static void DrawColider(const CShape& colider, const s3d::ColorF& color);
        static void DrawColider(const World& world);
        static void DrawMapColider(const World& world);

        static bool IsLogEffectNum();
        static void LogEffectNum(const Effects& effects);
    };
}

#endif