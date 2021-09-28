#pragma once

#if ABYSS_DEBUG
#include <memory>
#include <Siv3D/StringView.hpp>

#include <abyss/scenes/base/ISceneBase.hpp>
#include <abyss/utils/Singleton/Singleton.hpp>

namespace abyss::Debug
{
    class Profiler : protected Singleton<Profiler>
    {
        friend class Singleton<Profiler>;
    public:
        static void Begin(const s3d::StringView name);
        static void End(const s3d::StringView name);

        static void Print();
    private:
        Profiler();

    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}

#endif