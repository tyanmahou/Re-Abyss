#pragma once
#include <Siv3D/Optional.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IUpdate.hpp>
#include <abyss/components/Actor/Item/IItemReactor.hpp>
#include <abyss/components/Actor/Common/DeployId.hpp>
#include <abyss/components/Actor/Common/ShakeCtrl.hpp>

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
        ItemReactor(ActorObj* pActor, RecoveryKind kind);

        void onStart() override;
        void onUpdate() override;
        void onGained(ActorObj* player) override;
    private:
        ActorObj* m_pActor;
        RecoveryKind m_kind;
        Ref<DeployId> m_deployId;

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
