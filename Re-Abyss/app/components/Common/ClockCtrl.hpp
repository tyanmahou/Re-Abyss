#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
    class ITimeScale;

    class ClockCtrl final: public IComponent
    {
        GameObject* m_pObj;
        double m_deltaTime = 0.0;

        double m_updateTimeSec = 0.0;
        double m_drawTimeSec = 0.0;
        double m_timeScale = 1.0;

        s3d::Array<Ref<ITimeScale>> m_timeScaleComps;
    public:

        ClockCtrl(GameObject* pObj);

        void onStart() override;
        void updateDeltaTime(double dt);

        void updateUpdateTime();
        void updateDrawTime();

        s3d::Microseconds getUpdateTime() const;
        double getUpdateTimeSec() const;

        s3d::Microseconds getDrawTime() const;
        double getDrawTimeSec() const;

        double getDeltaTime() const;

        void resetDrawTime();
    };
}