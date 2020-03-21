#pragma once

#if ABYSS_DEBUG
#include <memory>
#include <abyss/utils/Singleton.hpp>

namespace abyss
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
    };
}

#endif