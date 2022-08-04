#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Builder.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/RetireCtrl.hpp>
#include <abyss/components/Actor/Enemy/BabyDux/Builder.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/utils/Coro/Task/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    Ref<ActorObj> KingDuxUtil::BuildTentacle(ActorObj* pActor, const TentacleDesc& desc)
    {
        return pActor->getModule<World>()->create<Tentacle::Builder>(pActor, Tentacle::BuildDesc{
            .offset = desc.offset,
            .rotate = s3d::ToRadians(desc.rotateDeg),
            .distOffset = desc.distOffset,
            .kind = desc.kind,
            .waitTimeSec = desc.waitTimeSec
            });
    }
    Ref<ActorObj> KingDuxUtil::BuildBaby(ActorObj* pActor, const BabyDux::BabyDesc& desc)
    {
        return pActor->getModule<World>()->create<BabyDux::Builder>(pActor, BabyDux::BuildDesc{
            .posOffset = desc.offset,
            .appearTime = desc.appearTime,
            .appearMove = desc.appearMove
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
    Coro::Task<void> KingDuxUtil::WaitTillStabAction(ActorObj* pActor, const s3d::Array<Ref<ActorObj>>& tentacles)
    {
        return RetireTask(pActor, tentacles) | WaitTillTentacle(tentacles);
    }
    Coro::Task<void> KingDuxUtil::WaitTillTentacleRetire(const s3d::Array<Ref<ActorObj>>& tentacles, s3d::int32 count)
    {
        return Coro::WaitUntil([&tentacles, count] {
            int32 retireCount = 0;
            for (auto&& obj : tentacles) {
                if (!obj || obj->find<Tentacle::RetireCtrl>()->isRetire()) {
                    ++retireCount;
                }
            }
            return retireCount >= count;
        });
    }
    Coro::Task<void> KingDuxUtil::RetireTask(ActorObj* pActor, const s3d::Array<Ref<ActorObj>>& tentacles, double timeOutSec, s3d::int32 count)
    {
        co_await (
            BehaviorUtil::WaitForSeconds(pActor, timeOutSec) |
            WaitTillTentacleRetire(tentacles, count)
            );

        RequestRetires(tentacles);

        co_await BehaviorUtil::Freeze();
    }
    Coro::Task<void> KingDuxUtil::WaitTillTentacle(const s3d::Array<Ref<ActorObj>>& tentacles)
    {
        co_await Coro::WaitUntil([&] {
            return tentacles.all([](const Ref<ActorObj>& obj) {
                return !obj;
            });
        });
    }
    void KingDuxUtil::RequestRetires(const s3d::Array<Ref<ActorObj>>& tentacles)
    {
        for (auto&& obj : tentacles) {
            if (!obj) {
                continue;
            }
            // リターンリクエスト
            obj->find<Tentacle::RetireCtrl>()->requestReturn();
        }

    }
}
