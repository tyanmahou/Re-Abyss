#include "ItemReactor.hpp"

#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/params/Actor/Item/Recovery/Param.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace
{
    using namespace abyss::Actor::Item;
    using namespace abyss::Actor::Item::Recovery;

    s3d::int32 RecoveryValue(RecoveryKind kind)
    {
        switch (kind) {
        case RecoveryKind::Small:
            return Param::Small.recoveryValue;
        case RecoveryKind::Big:
            return  Param::Small.recoveryValue;
        default:
        }
        return 0;
    }
}
namespace abyss::Actor::Item::Recovery
{
    ItemReactor::ItemReactor(ActorObj* pActor, RecoveryKind kind, const s3d::Optional<s3d::uint32>& objId) :
        m_pActor(pActor),
        m_kind(kind),
        m_objId(objId)
    {}
    void ItemReactor::onGained(ActorObj* player)
    {
        auto playerHp = player->find<HP>();
        if (!playerHp) {
            return;
        }

        // 体力回復
        playerHp->heal(::RecoveryValue(m_kind));
    }
}
