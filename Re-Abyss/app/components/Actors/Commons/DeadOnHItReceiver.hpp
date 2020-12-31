#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IPostCollision.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss::Actor
{
    class DeadOnHItReceiver :
        public IComponent,
        public IPostCollision
    {
        IActor* m_pActor;
        Ref<DeadChecker> m_deadChecker;
        Ref<MapCollider> m_mapCol;
        Ref<CollisionCtrl> m_cols;
    public:
        DeadOnHItReceiver(IActor* pActor);
        void onStart() override;
        void onPostCollision()override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DeadOnHItReceiver>
    {
        using Base = Actor::IPostCollision;
    };
}