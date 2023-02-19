#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/BaseState.hpp>
#include <abyss/modules/Camera/Quake/QuakeEpicenter.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{


    class WaitState final: public BaseState
    {
        class CameraTarget;
    public:
        void start()override;
        void end()override;
        Fiber<> task() override;
        void update() override;
    private:
        Ref<QuakeEpicenter> m_quake;
        std::shared_ptr<CameraTarget> m_cameraTarget;
    };
}
