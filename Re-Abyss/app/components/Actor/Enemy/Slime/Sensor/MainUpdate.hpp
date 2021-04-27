#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IUpdate.hpp>
#include <abyss/components/Actor/base/IPrePhysics.hpp>
#include <abyss/components/Actor/Commons/Locator.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::Slime::Sensor
{
    class ParentCtrl;

    class MainUpdate : 
        public IComponent,
        public IUpdate,
        public IPrePhysics
    {
        ActorObj* m_pActor;
        Ref<ParentCtrl> m_parentCtrl;
        Ref<MapCollider> m_mapColl;
        Ref<Locator> m_locator;
    public:
        MainUpdate(ActorObj* pActor);
        void onStart() override;
        void onUpdate() override;

        void onPrePhysics() override;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::Slime::Sensor::MainUpdate>
    {
        using Base = MultiComponents<Actor::IUpdate, Actor::IPrePhysics>;
    };
}