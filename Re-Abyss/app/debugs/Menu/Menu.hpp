#pragma once

#if ABYSS_DEBUG
#include <memory>
#include <Siv3D/StringView.hpp>
#include <abyss/utils/Singleton.hpp>

namespace abyss::Debug
{
    class Menu : protected Singleton<Menu>
    {
        friend class Singleton<Menu>;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;

        Menu();
    public:
        static bool IsDebug(s3d::StringView label);
        static void OnGUI();
        static void Release();
    };
}

#endif