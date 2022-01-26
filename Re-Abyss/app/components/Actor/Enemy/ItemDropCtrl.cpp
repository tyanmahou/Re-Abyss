#include <abyss/components/Actor/Enemy/ItemDropCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/World/World.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Item/Recovery/Builder.hpp>
#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>
#include <abyss/params/Actor/Item/Recovery/Param.hpp>
#include <Siv3D.hpp>
#include <ranges>
namespace
{
    using namespace abyss::Actor::Enemy;

    enum class DropItemKind
    {
        None,

        RecoverySmall,
        RecoveryMiddle,
        RecoveryBig,
    };
    using KindWeight = std::pair<DropItemKind, double>;

    s3d::Array<KindWeight> FindTable(ItemDropTableKind kind)
    {
        s3d::Array<KindWeight> ret;
        switch (kind) {
        case ItemDropTableKind::Normal:
            ret.reserve(4);
            ret.emplace_back(DropItemKind::None, 70.0);
            ret.emplace_back(DropItemKind::RecoverySmall, 30.0);
            ret.emplace_back(DropItemKind::RecoveryMiddle, 10.0);
            break;
        default:
            break;
        }
        return ret;
    }
}
namespace abyss::Actor::Enemy
{
    ItemDropCtrl::ItemDropCtrl(ActorObj* pActor, ItemDropTableKind tableKind) :
        m_pActor(pActor),
        m_tableKind(tableKind)
    {}
    Ref<ActorObj> ItemDropCtrl::drop() const
    {
        auto body = m_pActor->find<Body>();
        if (!body) {
            return nullptr;
        }
        auto table = ::FindTable(m_tableKind);
        if (table.isEmpty()) {
            return nullptr;
        }
        auto weights = table | std::views::transform([](const KindWeight& kindWeight) {
            return kindWeight.second;
        });
        DiscreteDistribution dist(weights.begin(), weights.end());
        auto choicedIndex = dist(GetDefaultRNG());
        auto dropKind = table[choicedIndex].first;

        Vec2 basePos = body->region().bottomCenter();

        auto world = m_pActor->getModule<World>();
        using abyss::Actor::Item::RecoveryKind;
        using abyss::Actor::Item::Recovery::Param;

        switch (dropKind) {
        case DropItemKind::None:
            return nullptr;
        case DropItemKind::RecoverySmall:
            return world->create<Item::Recovery::Builder>(basePos - Vec2{ 0, 20.0 }, RecoveryKind::Small);
        case DropItemKind::RecoveryMiddle:
            return world->create<Item::Recovery::Builder>(basePos - Vec2{ 0, 20.0}, RecoveryKind::Middle);
        case DropItemKind::RecoveryBig:
            return world->create<Item::Recovery::Builder>(basePos - Vec2{ 0, 20.0 }, RecoveryKind::Big);
        default:
            break;
        }
        return nullptr;
    }
}
