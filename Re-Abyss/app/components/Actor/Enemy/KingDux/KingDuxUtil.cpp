#include "KingDuxUtil.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Builder.hpp>
#include <Siv3D.hpp>
namespace abyss::Actor::Enemy::KingDux
{
    Ref<ActorObj> KindDuxUtil::BuildTentacle(ActorObj* pActor, const TentacleDesc& desc)
    {
        return pActor->getModule<World>()->create<Tentacle::Builder>(pActor, Tentacle::BuildDesc{
            .offset = desc.offset,
            .rotate = s3d::ToRadians(desc.rotateDeg)
            });
    }
}
