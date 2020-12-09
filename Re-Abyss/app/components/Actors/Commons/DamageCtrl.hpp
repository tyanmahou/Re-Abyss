#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ICollisionCallback.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss::Actor
{
    class DamageCtrl : 
        public IComponent,
        public ICollisionCallback
    {
    protected:
        Ref<HP> m_hp;
        IActor* m_pActor;
    public:
        DamageCtrl(IActor* pActor);

        void onStart() override;
        void onCollisionStay(ICollider* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DamageCtrl>
    {
        using Base = Actor::ICollisionCallback;
    };
}