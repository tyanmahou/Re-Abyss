#pragma once
#include <memory>
#include <Siv3D/Duration.hpp>
#include <abyss/models/GlobalTime/GlobalTimeScaleModel.hpp>

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
        std::function<s3d::Microseconds()> clock() const;

        double deltaTime() const;

        void pause() const;

        void resume() const;

        bool isPuase() const;

        void addTimeScale(const std::shared_ptr<GlobalTimeScaleModel>& timeScale);
    };
}