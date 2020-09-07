#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss::Actor::Player
{
    class AttackCtrl;

    class OopartsCtrl:
        public IComponent,
        public ILastUpdateModel
    {
    private:
        Ref<Ooparts::OopartsActor> m_mainOoparts;
        Ref<AttackCtrl> m_attackCtrl;
        Ref<BodyModel> m_body;
        IActor* m_pActor;
    public:
        OopartsCtrl(IActor* pActor);

        void setup() override;
        void onStart() override;

        OopartsCtrl& setMain(const Ref<Ooparts::OopartsActor>& main);

        void onLastUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::OopartsCtrl>
    {
        using Base = ILastUpdateModel;
    };
}