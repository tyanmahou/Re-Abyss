#pragma once
#include <abyss/modules/GameObject/Components.hpp>
#include <abyss/modules/Camera/CameraTarget/base/CameraTargetBase.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// カメラターゲット制御
    /// </summary>
    class CameraTarget :
        public IComponent
    {
        class Impl;
    public:
        CameraTarget(ActorObj* pActor, CameraTargetPriority priority);

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;
    private:
        ActorObj* m_pActor;
        std::shared_ptr<Impl> m_target;
    };
}