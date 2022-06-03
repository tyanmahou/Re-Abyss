#pragma once

#if ABYSS_DEBUG
#include <memory>
#include <Siv3D/StringView.hpp>

#include <abyss/scenes/base/ISceneBase.hpp>
#include <abyss/utils/Singleton/Singleton.hpp>

namespace abyss::Debug
{
    class Profiler
    {
    public:
        Profiler();

        void begin(const s3d::StringView name);
        void end(const s3d::StringView name);

        void print();
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}

#endif
