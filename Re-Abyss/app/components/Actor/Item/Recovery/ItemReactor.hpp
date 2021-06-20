#pragma once
#include <Siv3D/Optional.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IUpdate.hpp>
#include <abyss/components/Actor/Item/IItemReactor.hpp>
#include <abyss/components/Actor/Commons/ShakeCtrl.hpp>

#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Item::Recovery
{
    class ItemReactor :
        public IComponent,
        public IUpdate,
        public IItemReactor
    {
    public:
        ItemReactor(ActorObj* pActor, RecoveryKind kind, const s3d::Optional<s3d::uint32>& objId = s3d::none);

        void onStart() override;
        void onUpdate() override;
        void onGained(ActorObj* player) override;
    private:
        ActorObj* m_pActor;
        RecoveryKind m_kind;
        s3d::Optional<s3d::uint32> m_objId;

        bool m_isCollide = false;
        bool m_isCollideNext = false;

        Ref<ShakeCtrl> m_shake;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Item::Recovery::ItemReactor>
    {
        using Base = abyss::MultiComponents<
            Actor::IUpdate,
            Actor::Item::IItemReactor
        >;
    };
}