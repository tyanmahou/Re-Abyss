#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ICollisionReact.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss::Actor
{
    class DamageCtrl : 
        public IComponent,
        public ICollisionReact
    {
    protected:
        Ref<HP> m_hp;
        Ref<CollisionCtrl> m_colCtrl;
        IActor* m_pActor;
    public:
        DamageCtrl(IActor* pActor);

        void onStart() override;
        void onCollisionReact()override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DamageCtrl>
    {
        using Base = Actor::ICollisionReact;
    };
}