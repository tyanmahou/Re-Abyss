#pragma once
#include <abyss/models/Actors/Commons/DamageModel.hpp>
namespace abyss::Actor::Enemy::Schield
{
    class FaceCtrlModel;

    class DamageModel :
        public abyss::DamageModel
    {
        Ref<FaceCtrlModel> m_face;
    public:
        DamageModel(IActor* pActor);

        void setup() override;

        void onCollisionStay(IActor* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::Schield::DamageModel>
    {
        using Base = abyss::DamageModel;
    };
}