#include <abyss/components/Actor/Enemy/CodeZero/Behavior.hpp>

#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/Builder.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>

#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/utils/Coro/Task/Wait.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Coro::AsyncGenerator<BehaviorFunc> BehaviorSequence::Root(ActorObj* pActor)
    {
        // 前半パターン
        co_yield Behavior::Phase1;

        // HP 2/3まで
        co_await BehaviorUtil::WaitLessThanHpRate(pActor, 2.0 / 3.0);
        co_await Behavior::WaitPursuitHands(pActor);

        // 中盤パターン
        co_yield Behavior::Phase2;

        // HP 1/3まで
        co_await BehaviorUtil::WaitLessThanHpRate(pActor, 1.0 / 3.0);
        co_await Behavior::WaitPursuitHands(pActor);

        // 後半パターン
        co_yield Behavior::Phase3;
    }
    Coro::Task<> Behavior::Phase1(ActorObj* pActor)
    {
        co_await Appear(pActor);

        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase1::WaitRestart);

        while (true) {
            // 左手攻撃
            co_await LeftAttackAndWait(pActor, Param::Phase1::WaitAttack);

            // 右手攻撃
            co_await RightAttackAndWait(pActor, Param::Phase2::WaitRestart);
        }
        co_return;
    }

    Coro::Task<> Behavior::Phase2(ActorObj* pActor)
    {
        co_await Angry(pActor);

        // 追従開始
        co_await ChangeHandsPhase2(pActor);

        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase2::WaitInit);

        while (true) {
            // 右手攻撃
            co_await RightAttackAndWait(pActor, Param::Phase2::WaitAttack);

            // 左手攻撃
            co_await LeftAttackAndWait(pActor, Param::Phase2::WaitDualAttack);

            // 両手攻撃
            co_await BothAttackAndWait(pActor, Param::Phase2::WaitRestart);
        }
        co_return;
    }

    Coro::Task<> Behavior::Phase3(ActorObj* pActor)
    {
        co_await Angry(pActor);

        bool isReverse = false;
        while (true) {

            // ショット攻撃
            co_await ChargeShot(pActor);

            // 待機
            co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase3::WaitPursuit);

            // 回転攻撃
            co_await RollingAttack(pActor, isReverse);
            isReverse = !isReverse;

            constexpr bool slowStart = true;
            if (isReverse) {
                co_await ChangeHandsPhase1(pActor, slowStart);
            } else {
                co_await ChangeHandsPhase2(pActor, slowStart);
            }

            // 待機
            co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase3::WaitInitAttack);

            // 二回手攻撃
            for ([[maybe_unused]]int32 count : step(2)) {
                // 右手攻撃
                co_await RightAttackAndWait(pActor, Param::Phase3::WaitAttack);

                // 左手攻撃
                co_await LeftAttackAndWait(pActor, Param::Phase3::WaitAttack);

                // 右手攻撃
                co_await RightAttackAndWait(pActor, Param::Phase3::WaitRestart);
            }
        }
        co_return;
    }
    Coro::Task<> Behavior::Appear(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<AppearState>();
        co_yield{};
    }
    Coro::Task<> Behavior::Angry(ActorObj* pActor)
    {
        co_return;
    }
    Coro::Task<> Behavior::Dead(ActorObj* pActor)
    {
        pActor->find<DeadChecker>()->requestDead();
        co_yield{};
    }
    Coro::Task<> Behavior::LeftAttack(ActorObj* pActor)
    {
        pActor->find<PartsCtrl>()->getLeftHand()->tryAttack();
        co_return;
    }

    Coro::Task<> Behavior::RightAttack(ActorObj* pActor)
    {
        pActor->find<PartsCtrl>()->getRightHand()->tryAttack();
        co_return;
    }

    Coro::Task<> Behavior::BothAttack(ActorObj* pActor)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        parts->getLeftHand()->tryAttack();
        parts->getRightHand()->tryAttack();
        co_return;
    }

    Coro::Task<> Behavior::LeftAttackAndWait(ActorObj* pActor, double waitSec)
    {
        co_await LeftAttack(pActor);
        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, waitSec);
    }

    Coro::Task<> Behavior::RightAttackAndWait(ActorObj* pActor, double waitSec)
    {
        // 右手攻撃
        co_await RightAttack(pActor);
        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, waitSec);
    }

    Coro::Task<> Behavior::BothAttackAndWait(ActorObj* pActor, double waitSec)
    {
        // 両手攻撃
        co_await BothAttack(pActor);
        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, waitSec);
    }

    Coro::Task<> Behavior::RollingAttack(ActorObj* pActor, bool isReverse)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        parts->getLeftHand()->tryRollingAttack(isReverse);
        parts->getRightHand()->tryRollingAttack(isReverse);

        co_await WaitPursuitHands(pActor);
    }

    Coro::Task<> Behavior::ChargeShot(ActorObj* pActor)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        // チャージ開始
        parts->getRightHand()->tryShotCharge();
        parts->getLeftHand()->tryShotCharge();

        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase3::WaitShot);

        // ショット生成
        pActor->getModule<World>()->create<Shot::Builder>(pActor);
    }

    Coro::Task<> Behavior::ChangeHandsPhase1(ActorObj* pActor, bool slowStart)
    {
        auto parts = pActor->find<PartsCtrl>().get();
        parts->getLeftHand()->tryPursuit(Hand::HandDesc::CreateLeftPhase1(), slowStart);
        parts->getRightHand()->tryPursuit(Hand::HandDesc::CreateRightPhase1(), slowStart);
        co_return;
    }

    Coro::Task<> Behavior::ChangeHandsPhase2(ActorObj* pActor, bool slowStart)
    {
        auto parts = pActor->find<PartsCtrl>().get();
        parts->getLeftHand()->tryPursuit(Hand::HandDesc::CreateLeftPhase2(), slowStart);
        parts->getRightHand()->tryPursuit(Hand::HandDesc::CreateRightPhase2(), slowStart);
        co_return;
    }

    Coro::Task<> Behavior::WaitPursuitHands(ActorObj* pActor)
    {
        auto parts = pActor->find<PartsCtrl>();
        co_await Coro::WaitUntil([parts] {
            return parts->getLeftHand()->isPursuit() &&
                parts->getRightHand()->isPursuit();
        });
    }
}
