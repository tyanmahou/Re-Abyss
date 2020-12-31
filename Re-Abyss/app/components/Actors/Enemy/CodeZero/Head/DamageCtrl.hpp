#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IPostCollision.hpp>
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
        public IPostCollision
    {
    protected:
        Ref<CollisionCtrl> m_col;
        Ref<ParentCtrl> m_parent;
        IActor* m_pActor;
    public:
        DamageCtrl(IActor* pActor);

        void onStart() override;
        void onPostCollision()override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::Head::DamageCtrl>
    {
        using Base = Actor::IPostCollision;
    };
}