#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Player/IGimmickReactor.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Actor::Item
{
    class IItemReactor;

    class ItemCollision :
        public IComponent,
        public Player::IGimmickReactor
    {
    public:
        ItemCollision(ActorObj* pActor);

        void setup(Executer executer);
        void onStart() override;
        void onGimmickReact(ActorObj* player) override;
    private:
        ActorObj* m_pActor;
        Ref<Col::ICollider> m_collider;
        s3d::Array<Ref<IItemReactor>> m_reactors;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Item::ItemCollision>
    {
        using Base = Actor::Player::IGimmickReactor;
    };
}