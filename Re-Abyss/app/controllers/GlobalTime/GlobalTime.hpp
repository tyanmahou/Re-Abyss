#pragma once
#include <memory>
#include <Siv3D/Duration.hpp>
#include <abyss/utils/Singleton.hpp>

using namespace std::literals;

namespace abyss
{
    class GlobalTime
    {
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;

    public:
        GlobalTime();
        ~GlobalTime();
        void update() const;

        double time() const;
        s3d::Microseconds timeMicroSec() const;

       double deltaTime() const;

        void pause() const;

        void resume() const;

        void setTimeScale(double timeScale) const;

        bool isPuase() const;
    };
}