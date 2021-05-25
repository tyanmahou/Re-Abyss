#pragma once

#if ABYSS_DEBUG
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Debug
{
    class DebugManager : protected DynamicSingleton<DebugManager>
    { 
        friend class DynamicSingleton<DebugManager>;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;

        DebugManager();
    public:
        static void Update();

        static void DrawDebug(const World& world);

        static void DrawDebug(const Effects& effects);

        static void DrawDebug(const Decors& decor);
    };
}

#endif