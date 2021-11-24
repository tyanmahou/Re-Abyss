#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPrePhysics.hpp>
#include <abyss/components/Actor/base/IPostPhysics.hpp>
#include <abyss/components/Actor/Common/Locator.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::Slime::Sensor
{
    class ParentCtrl;

    class MainUpdate : 
        public IComponent,
        public IPrePhysics,
        public IPostPhysics
    {
        ActorObj* m_pActor;
        Ref<ParentCtrl> m_parentCtrl;
        Ref<MapCollider> m_mapColl;
        Ref<Locator> m_locator;
    public:
        MainUpdate(ActorObj* pActor);
        void setup(Executer executer);
        void onStart() override;

        void onPrePhysics() override;
        void onPostPhysics() override;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::Slime::Sensor::MainUpdate>
    {
        using Base = MultiComponents<Actor::IPrePhysics, Actor::IPostPhysics>;
    };
}