#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/Player/IGimmickReactor.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Gimmick::Door
{
    class DoorProxy;

    class GimmickReactor : 
        public IComponent,
        public Player::IGimmickReactor
    {
    public:
        GimmickReactor(ActorObj* pActor);

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
    struct ComponentTree<Actor::Gimmick::Door::GimmickReactor>
    {
        using Base = Actor::Player::IGimmickReactor;
    };
}