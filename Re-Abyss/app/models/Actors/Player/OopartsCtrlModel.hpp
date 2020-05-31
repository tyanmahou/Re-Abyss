#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss::Player
{
    class AttackCtrlModel;

    class OopartsCtrlModel:
        public IComponent,
        public ILastUpdateModel
    {
    private:
        Ref<Ooparts::OopartsActor> m_mainOoparts;
        Ref<AttackCtrlModel> m_attackCtrl;
        Ref<BodyModel> m_body;
        IActor* m_pActor;
    public:
        OopartsCtrlModel(IActor* pActor);

        void setup() override;

        OopartsCtrlModel& setMain(const Ref<Ooparts::OopartsActor>& main);

        void onLastUpdate(double dt) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Player::OopartsCtrlModel>
    {
        using Base = ILastUpdateModel;
    };
}