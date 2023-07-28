#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Builder.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/RetireCtrl.hpp>
#include <abyss/components/Actor/Enemy/BabyDux/Builder.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    Ref<ActorObj> KingDuxUtil::BuildTentacle(ActorObj* pActor, const TentacleDesc& desc)
    {
        return pActor->getModule<Actors>()->create<Tentacle::Builder>(pActor, Tentacle::BuildDesc{
            .offset = desc.offset,
            .rotate = s3d::ToRadians(desc.rotateDeg),
            .distOffset = desc.distOffset,
            .kind = desc.kind,
            .waitTimeSec = desc.waitTimeSec
            });
    }
    Ref<ActorObj> KingDuxUtil::BuildBaby(ActorObj* pActor, const BabyDux::BabyDesc& desc)
    {
        return pActor->getModule<Actors>()->create<BabyDux::Builder>(pActor, BabyDux::BuildDesc{
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
    Coro::Fiber<void> KingDuxUtil::WaitTillStabAction(ActorObj* pActor, const s3d::Array<Ref<ActorObj>>& tentacles)
    {
        return RetireFiber(pActor, tentacles) | WaitTillTentacle(tentacles);
    }
    Coro::Fiber<void> KingDuxUtil::WaitTillTentacleRetire(const s3d::Array<Ref<ActorObj>>& tentacles, s3d::int32 count)
    {
        return Coro::FiberUtil::WaitUntil([&tentacles, count] {
            int32 retireCount = 0;
            for (auto&& obj : tentacles) {
                if (!obj || obj->find<Tentacle::RetireCtrl>()->isRetire()) {
                    ++retireCount;
                }
            }
            return retireCount >= count;
        });
    }
    Coro::Fiber<void> KingDuxUtil::RetireFiber(ActorObj* pActor, const s3d::Array<Ref<ActorObj>>& tentacles, double timeOutSec, s3d::int32 count)
    {
        co_await (
            BehaviorUtil::WaitForSeconds(pActor, timeOutSec) |
            WaitTillTentacleRetire(tentacles, count)
            );

        RequestRetires(tentacles);

        co_await BehaviorUtil::Freeze();
    }
    Coro::Fiber<void> KingDuxUtil::WaitTillTentacle(const s3d::Array<Ref<ActorObj>>& tentacles)
    {
        co_await Coro::FiberUtil::WaitUntil([&] {
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
