#pragma once
#include <memory>
#include <Siv3D/Duration.hpp>
#include <Siv3D/ISteadyClock.hpp>
#include <abyss/modules/GlobalTime/GlobalTimeScale.hpp>

using namespace std::literals;

namespace abyss
{
    class GlobalTime : public s3d::ISteadyClock
    {
    public:
        GlobalTime();
        ~GlobalTime();
        void update() const;

        double time() const;
        s3d::Microseconds timeMicroSec() const;
        std::function<s3d::Microseconds()> clock() const;

        double deltaTime() const;

        void pause() const;

        void resume() const;

        bool isPuase() const;

        void addTimeScale(const std::shared_ptr<GlobalTimeScale>& timeScale);
        std::shared_ptr<GlobalTimeScale> createAddTimeScale();
    private:
        s3d::uint64 getMicrosec() override;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;

    };
}
