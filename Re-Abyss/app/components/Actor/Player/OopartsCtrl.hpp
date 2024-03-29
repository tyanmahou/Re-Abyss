#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/ILastUpdate.hpp>

namespace abyss::Actor::Player
{
    class AttackCtrl;

    class OopartsCtrl:
        public IComponent,
        public ILastUpdate
    {
    private:
        Ref<ActorObj> m_mainOoparts;
        Ref<AttackCtrl> m_attackCtrl;
        Ref<Body> m_body;
        ActorObj* m_pActor;
    public:
        OopartsCtrl(ActorObj* pActor);

        void onStart() override;

        OopartsCtrl& setMain(const Ref<ActorObj>& main);

        void onLastUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::OopartsCtrl>
    {
        using Base = Actor::ILastUpdate;
    };
}