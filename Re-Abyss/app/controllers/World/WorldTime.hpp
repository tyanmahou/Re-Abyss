#pragma once
#include <memory>
#include <Siv3D/Duration.hpp>
#include <abyss/utils/Singleton.hpp>

namespace abyss
{
    class WorldTime : protected Singleton<WorldTime>
    {
        friend class Singleton<WorldTime>;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
        WorldTime();
    public:
        static void Update();

        static double Time();
        static s3d::Microseconds TimeMicroSec();

        static double DeltaTime();

        static void Pause();

        static void Resume();

        static void SetTimeScale(double timeScale);
    };
}