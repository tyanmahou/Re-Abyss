#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ICollisionReact.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class ParentCtrl;
}
namespace abyss::Actor::Enemy::CodeZero::Head
{
    class DamageCtrl :
        public IComponent,
        public ICollisionReact
    {
    protected:
        Ref<CollisionCtrl> m_col;
        Ref<ParentCtrl> m_parent;
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
    struct ComponentTree<Actor::Enemy::CodeZero::Head::DamageCtrl>
    {
        using Base = Actor::ICollisionReact;
    };
}