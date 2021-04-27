#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/Player/IGimmickReacter.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Gimmick::Door
{
    class DoorProxy;

    class GimmickReacter : 
        public IComponent,
        public Player::IGimmickReacter
    {
    public:
        GimmickReacter(ActorObj* pActor);

        void onStart() override;
        void onGimmickReact(ActorObj* player) override;
    private:
        ActorObj* m_pActor;
        Ref<DoorProxy> m_door;
        Ref<ICollider> m_collider;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Gimmick::Door::GimmickReacter>
    {
        using Base = Actor::Player::IGimmickReacter;
    };
}