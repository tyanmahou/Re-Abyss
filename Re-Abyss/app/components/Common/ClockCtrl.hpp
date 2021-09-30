#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/ISteadyClock.hpp>

namespace abyss
{
    class ITimeScale;

    class ClockCtrl final: public IComponent
    {
    public:

        ClockCtrl(GameObject* pObj);

        void onStart() override;
        void updateDeltaTime(double dt);
        void setTimeScale(double timeScale);

        void updateUpdateTime();
        void updateDrawTime();

        s3d::Microseconds getUpdateTime() const;
        double getUpdateTimeSec() const;

        s3d::ISteadyClock* getUpdateClock();

        s3d::Microseconds getDrawTime() const;
        double getDrawTimeSec() const;

        s3d::ISteadyClock* getDrawClock();

        double getDeltaTime() const;

        void resetDrawTime();
    private:
        GameObject* m_pObj;
        double m_deltaTime = 0.0;

        double m_updateTimeSec = 0.0;
        double m_drawTimeSec = 0.0;
        double m_timeScale = 1.0;
        double m_timeScaleBase = 1.0;

        s3d::Array<Ref<ITimeScale>> m_timeScaleComps;

        struct UpdateClock : s3d::ISteadyClock
        {
            ClockCtrl* owner;
            UpdateClock(ClockCtrl* o):
                owner(o)
            {}
            s3d::uint64 getMicrosec() override
            {
                return owner->getUpdateTime().count();
            }
        }m_updateClock;

        struct DrawClock : s3d::ISteadyClock
        {
            ClockCtrl* owner;
            DrawClock(ClockCtrl* o) :
                owner(o)
            {}
            s3d::uint64 getMicrosec() override
            {
                return owner->getDrawTime().count();
            }
        }m_drawClock;
    };
}