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

    namespace ProfKind
    {
        inline static constexpr s3d::StringView UpdateAll       = U"Update All";
        inline static constexpr s3d::StringView DrawAll         = U"Draw All";
        inline static constexpr s3d::StringView DrawReuqest     = U"  Draw Reuqest";
        inline static constexpr s3d::StringView DrawBackGround  = U"  Draw BackGround";
        inline static constexpr s3d::StringView DrawDecorBack   = U"  Draw DecorBack";
        inline static constexpr s3d::StringView DrawDecorMiddle = U"  Draw DecorMiddle";
        inline static constexpr s3d::StringView DrawWorld       = U"  Draw World";
        inline static constexpr s3d::StringView DrawDecorFront  = U"  Draw DecorFront";
        inline static constexpr s3d::StringView DrawLight       = U"  Draw Light";
        inline static constexpr s3d::StringView DrawDist        = U"  Draw Dist";
        inline static constexpr s3d::StringView DrawDebug       = U"  Draw Debug";
        inline static constexpr s3d::StringView DrawPostEffect  = U"  Draw PostEffect";
        inline static constexpr s3d::StringView DrawUI          = U"  Draw UI";
    }
}

#endif