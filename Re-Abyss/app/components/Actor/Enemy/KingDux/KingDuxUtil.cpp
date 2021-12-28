#include "KingDuxUtil.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Builder.hpp>
#include <Siv3D.hpp>
namespace abyss::Actor::Enemy::KingDux
{
    Ref<ActorObj> KingDuxUtil::BuildTentacle(ActorObj* pActor, const TentacleDesc& desc)
    {
        return pActor->getModule<World>()->create<Tentacle::Builder>(pActor, Tentacle::BuildDesc{
            .offset = desc.offset,
            .rotate = s3d::ToRadians(desc.rotateDeg),
            .kind = desc.kind,
            .waitTimeSec = desc.waitTimeSec
            });
    }
    void KingDuxUtil::SetVisible(ActorObj* pActor, bool isVisible)
    {
        pActor->find<VModel>()->setVisible(isVisible);
        pActor->find<VModelSub<1>>()->setVisible(isVisible);
        pActor->find<VModelSub<2>>()->setVisible(isVisible);
        pActor->find<VModelSub<3>>()->setVisible(isVisible);
        pActor->find<VModelSub<4>>()->setVisible(isVisible);
    }
}
