#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPostCollision.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss::Actor
{
    class DeadOnHItReceiver :
        public IComponent,
        public IPostCollision
    {
        ActorObj* m_pActor;
        Ref<DeadChecker> m_deadChecker;
        Ref<MapCollider> m_mapCol;
        Ref<ColCtrl> m_cols;
    public:
        DeadOnHItReceiver(ActorObj* pActor);
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