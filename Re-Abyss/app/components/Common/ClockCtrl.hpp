#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/ISteadyClock.hpp>

namespace abyss
{
    class ITimeScale;

    class ClockCtrl final:
        public IComponent,
        public s3d::ISteadyClock
    {
    public:

        ClockCtrl(GameObject* pObj);

        void onStart() override;

        void updateDeltaTime(double dt);

        double getDeltaTime() const;

        void setTimeScale(double timeScale);

        void updateTime();

        s3d::Microseconds getTime() const;
        double getTimeSec() const;

        s3d::ISteadyClock* getClock();

        void resetTime();
    private:
        s3d::uint64 getMicrosec() override;
    private:
        GameObject* m_pObj;
        double m_deltaTime = 0.0;

        double m_timeSec = 0.0;

        double m_timeScale = 1.0;
        double m_timeScaleBase = 1.0;

        s3d::Array<Ref<ITimeScale>> m_timeScaleComps;
    };
}