#pragma once
#include <abyss/components/Actor/Item/IItemReactor.hpp>
#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>

namespace abyss::Actor::Item::Recovery
{
    class ItemReactor : public IItemReactor
    {
    public:
        ItemReactor(ActorObj* pActor, RecoveryKind kind, const s3d::Optional<s3d::uint32>& objId = s3d::none);

        void onGained(ActorObj* player) override;
    private:
        ActorObj* m_pActor;
        RecoveryKind m_kind;
        s3d::Optional<s3d::uint32> m_objId;
    };
}