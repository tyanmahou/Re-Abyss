#pragma once

#if ABYSS_DEBUG
#include <memory>
#include <Siv3D/StringView.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss::Debug
{
    class Menu : protected DynamicSingleton<Menu>
    {
        friend class DynamicSingleton<Menu>;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;

        Menu();
    public:
        static bool IsDebug(s3d::StringView label);
        static void OnGUI();
    };
}

#endif