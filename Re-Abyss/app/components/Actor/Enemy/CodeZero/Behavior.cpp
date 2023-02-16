#include <abyss/components/Actor/Enemy/CodeZero/Behavior.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Novel/Novels.hpp>

#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/AngryState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/ShotState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>

#include <abyss/components/Novel/CodeZeroDemo/SignalCtrl.hpp>

#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Coro::AsyncGenerator<BehaviorFunc> BehaviorSequence::Root(ActorObj* pActor)
    {
        // 前半パターン
        co_yield Behavior::Phase1;

        // HP 2/3まで
        co_await BehaviorUtil::WaitLessThanHpRate(pActor, 2.0 / 3.0);

        // 中盤パターン
        co_yield Behavior::Phase2;

        // HP 1/3まで
        co_await BehaviorUtil::WaitLessThanHpRate(pActor, 1.0 / 3.0);

        // 後半パターン
        co_yield Behavior::Phase3;
    }
    Coro::Fiber<> Behavior::Phase1(ActorObj* pActor)
    {
        co_await TryToAppear(pActor);

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

    Coro::Fiber<> Behavior::Phase2(ActorObj* pActor)
    {
        co_await Angry(pActor);

        co_await Behavior::WaitPursuitHands(pActor);

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

    Coro::Fiber<> Behavior::Phase3(ActorObj* pActor)
    {
        co_await Angry(pActor);

        co_await Behavior::WaitPursuitHands(pActor);

        bool isReverse = false;
        while (true) {

            // ショット攻撃
            co_await ChargeShot(pActor);

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
    Coro::Fiber<> Behavior::TryToAppear(ActorObj* pActor)
    {
        if (pActor->getModule<Novels>()->find<Novel::CodeZeroDemo::SignalCtrl>()) {
            co_await Appear(pActor);
        }
    }
    Coro::Fiber<> Behavior::Appear(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<AppearState>();
        co_yield{};
    }
    Coro::Fiber<> Behavior::Angry(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<AngryState>();
        co_yield{};
    }
    Coro::Fiber<> Behavior::Dead(ActorObj* pActor)
    {
        pActor->find<DeadChecker>()->requestDead();
        co_yield{2};
    }
    Coro::Fiber<> Behavior::LeftAttack(ActorObj* pActor)
    {
        pActor->find<PartsCtrl>()->getLeftHand()->tryAttack();
        co_return;
    }

    Coro::Fiber<> Behavior::RightAttack(ActorObj* pActor)
    {
        pActor->find<PartsCtrl>()->getRightHand()->tryAttack();
        co_return;
    }

    Coro::Fiber<> Behavior::BothAttack(ActorObj* pActor)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        parts->getLeftHand()->tryAttack();
        parts->getRightHand()->tryAttack();
        co_return;
    }

    Coro::Fiber<> Behavior::LeftAttackAndWait(ActorObj* pActor, double waitSec)
    {
        co_await LeftAttack(pActor);
        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, waitSec);
    }

    Coro::Fiber<> Behavior::RightAttackAndWait(ActorObj* pActor, double waitSec)
    {
        // 右手攻撃
        co_await RightAttack(pActor);
        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, waitSec);
    }

    Coro::Fiber<> Behavior::BothAttackAndWait(ActorObj* pActor, double waitSec)
    {
        // 両手攻撃
        co_await BothAttack(pActor);
        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, waitSec);
    }

    Coro::Fiber<> Behavior::RollingAttack(ActorObj* pActor, bool isReverse)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        parts->getLeftHand()->tryRollingAttack(isReverse);
        parts->getRightHand()->tryRollingAttack(isReverse);

        co_await WaitPursuitHands(pActor);
    }

    Coro::Fiber<> Behavior::ChargeShot(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<ShotState>();
        co_yield{};
    }

    Coro::Fiber<> Behavior::ChangeHandsPhase1(ActorObj* pActor, bool slowStart)
    {
        auto parts = pActor->find<PartsCtrl>().get();
        parts->getLeftHand()->tryPursuit(Hand::HandDesc::CreateLeftPhase1(), slowStart);
        parts->getRightHand()->tryPursuit(Hand::HandDesc::CreateRightPhase1(), slowStart);
        co_return;
    }

    Coro::Fiber<> Behavior::ChangeHandsPhase2(ActorObj* pActor, bool slowStart)
    {
        auto parts = pActor->find<PartsCtrl>().get();
        parts->getLeftHand()->tryPursuit(Hand::HandDesc::CreateLeftPhase2(), slowStart);
        parts->getRightHand()->tryPursuit(Hand::HandDesc::CreateRightPhase2(), slowStart);
        co_return;
    }
    Coro::Fiber<> Behavior::Wait(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<WaitState>();
        co_yield{};
    }
    Coro::Fiber<> Behavior::WaitPursuitHands(ActorObj* pActor)
    {
        auto parts = pActor->find<PartsCtrl>();
        co_await Coro::WaitUntil([parts] {
            return parts->getLeftHand()->isPursuit() &&
                parts->getRightHand()->isPursuit();
        });
    }
}
