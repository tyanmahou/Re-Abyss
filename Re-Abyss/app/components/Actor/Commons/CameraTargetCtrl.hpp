#pragma once
#include <abyss/components/base/Components.hpp>
#include <abyss/modules/Camera/CameraTarget/base/CameraTargetBase.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// カメラターゲット制御
    /// </summary>
    class CameraTargetCtrl :
        public IComponent
    {
        class CameraTarget;
    public:
        CameraTargetCtrl(ActorObj* pActor, CameraTargetPriorityType priority);

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;
    private:
        ActorObj* m_pActor;
        std::shared_ptr<CameraTarget> m_target;
    };
}