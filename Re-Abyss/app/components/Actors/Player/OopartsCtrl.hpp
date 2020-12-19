#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ILastUpdate.hpp>

namespace abyss::Actor::Player
{
    class AttackCtrl;

    class OopartsCtrl:
        public IComponent,
        public ILastUpdate
    {
    private:
        Ref<IActor> m_mainOoparts;
        Ref<AttackCtrl> m_attackCtrl;
        Ref<Body> m_body;
        IActor* m_pActor;
    public:
        OopartsCtrl(IActor* pActor);

        void onStart() override;

        OopartsCtrl& setMain(const Ref<IActor>& main);

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