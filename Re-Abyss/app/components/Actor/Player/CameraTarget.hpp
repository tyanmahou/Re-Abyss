#pragma once
#include <abyss/components/base/Components.hpp>
#include <abyss/components/Actor/base/IPostPhysics.hpp>
#include <abyss/modules/Camera/CameraTarget/base/CameraTargetBase.hpp>

namespace abyss::Actor::Player
{
    /// <summary>
    /// カメラターゲット制御
    /// </summary>
    class CameraTarget :
        public IComponent,
        public IPostPhysics
    {
        class Impl;
    public:
        CameraTarget(ActorObj* pActor);

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;
        void onPostPhysics() override;
    private:
        ActorObj* m_pActor;
        std::shared_ptr<Impl> m_target;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::CameraTarget>
    {
        using Base = Actor::IPostPhysics;
    };
}