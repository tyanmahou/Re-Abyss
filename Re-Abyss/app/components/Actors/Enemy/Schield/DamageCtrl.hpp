#pragma once
#include <abyss/models/Actors/Commons/DamageModel.hpp>
namespace abyss::Actor::Enemy::Schield
{
    class FaceCtrl;

    class DamageCtrl :
        public abyss::DamageModel
    {
        Ref<FaceCtrl> m_face;
    public:
        DamageCtrl(IActor* pActor);

        void setup() override;

        void onCollisionStay(IActor* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::Schield::DamageCtrl>
    {
        using Base = abyss::DamageModel;
    };
}