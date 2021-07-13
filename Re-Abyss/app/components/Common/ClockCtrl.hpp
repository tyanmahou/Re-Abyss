#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Clock/Clock.hpp>
namespace abyss
{
    class ClockCtrl final: public IComponent
    {
        double m_deltaTime = 0.0;

        double m_updateTimeSec = 0.0;
        double m_drawTimeSec = 0.0;
        double m_timeScale = 1.0;
    public:
        void updateDeltaTime(double dt);

        void updateUpdateTime();
        void updateDrawTime();

        void setTimeScale(double timeScale);

        s3d::Microseconds getUpdateTime() const;
        double getUpdateTimeSec() const;

        s3d::Microseconds getDrawTime() const;
        double getDrawTimeSec() const;

        double getDeltaTime() const;

        void resetDrawTime();
    };
}