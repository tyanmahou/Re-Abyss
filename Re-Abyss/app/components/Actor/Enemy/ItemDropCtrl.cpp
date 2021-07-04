#include "ItemDropCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy
{
    ItemDropCtrl::ItemDropCtrl(ActorObj* pActor) :
        m_pActor(pActor)
    {}
    void ItemDropCtrl::drop() const
    {
        // TODO 生成
        auto world = m_pActor->getModule<World>();

        using abyss::Actor::Item::RecoveryKind;
        DiscreteDistribution dist({ 70.0f, 25.0f, 5.0f });
        auto type = static_cast<Actor::Item::RecoveryKind>(dist(GetDefaultRNG()));
        switch (type) {
        case RecoveryKind::None:
            break;
        case RecoveryKind::Small:
            break;
        case RecoveryKind::Middle:
            break;
        case RecoveryKind::Big:
            break;
        default:
            break;
        }
    }
}
