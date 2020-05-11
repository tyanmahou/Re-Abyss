#pragma once

#if ABYSS_DEBUG
#include <memory>
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
        static bool DisableDarkNess();

        static void DrawColider(const CShape& colider);
    };
}

#endif