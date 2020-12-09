#pragma once
#include <abyss/components/Actors/Commons/DamageCtrl.hpp>
namespace abyss::Actor::Enemy::Schield
{
    class FaceCtrl;

    class DamageCtrl :
        public Actor::DamageCtrl
    {
        Ref<FaceCtrl> m_face;
    public:
        DamageCtrl(IActor* pActor);

        void onStart() override;

        void onCollisionStay(ICollider* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::Schield::DamageCtrl>
    {
        using Base = Actor::DamageCtrl;
    };
}