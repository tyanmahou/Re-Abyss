#include <abyss/components/Actor/Enemy/CodeZero/Behavior.hpp>

#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/Builder.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>

#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Coro::Task<> BehaviorSequence::Root(BehaviorCtrl* behavior)
    {
        auto* pActor = behavior->getActor();

        // 前半パターン
        behavior->setBehavior(Behavior::Pettern1);

        // HP 2/3まで
        co_await BehaviorUtil::WaitLessThanHpRate(pActor, 2.0 / 3.0);
        co_await Behavior::WaitPursuitHands(pActor);

        // 中盤パターン
        behavior->setBehavior(Behavior::Pettern2);

        // HP 1/3まで
        co_await BehaviorUtil::WaitLessThanHpRate(pActor, 1.0 / 3.0);
        co_await Behavior::WaitPursuitHands(pActor);

        // 後半パターン
        behavior->setBehavior(Behavior::Pettern3);
    }
    Coro::Task<> Behavior::Pettern1(ActorObj* pActor)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase1::WaitRestart);

        while (true) {
            // 左手攻撃
            parts->getLeftHand()->tryAttack();

            // 待機
            co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase1::WaitAttack);

            // 右手攻撃
            parts->getRightHand()->tryAttack();

            // 待機
            co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase2::WaitRestart);
        }
        co_return;
    }

    Coro::Task<> Behavior::Pettern2(ActorObj* pActor)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        // 追従開始
        parts->getLeftHand()->tryPursuit(Hand::HandDesc::CreateLeftPhase2());
        parts->getRightHand()->tryPursuit(Hand::HandDesc::CreateRightPhase2());

        // 待機
        co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase2::WaitInit);

        while (true) {
            // 右手攻撃
            parts->getRightHand()->tryAttack();

            // 待機
            co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase2::WaitAttack);

            // 左手攻撃
            parts->getLeftHand()->tryAttack();

            // 待機
            co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase2::WaitDualAttack);

            // 両手攻撃
            parts->getRightHand()->tryAttack();
            parts->getLeftHand()->tryAttack();

            // 待機
            co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase2::WaitRestart);
        }
        co_return;
    }

    Coro::Task<> Behavior::Pettern3(ActorObj* pActor)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        // 1ループ目だけ長め
        double waitShotSec = Param::Phase3::WaitPursuit;
        bool isReverse = false;
        while (true) {

            // チャージ開始
            parts->getRightHand()->tryShotCharge();
            parts->getLeftHand()->tryShotCharge();

            // 待機
            co_await BehaviorUtil::WaitForSeconds(pActor, waitShotSec);
            waitShotSec = Param::Phase3::WaitShot;

            // ショット生成
            pActor->getModule<World>()->create<Shot::Builder>(pActor);

            // 待機
            co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase3::WaitPursuit);

            // 追従開始
            parts->getLeftHand()->tryRollingAttack(isReverse);
            parts->getRightHand()->tryRollingAttack(isReverse);

            isReverse = !isReverse;

            while (!(parts->getLeftHand()->isPursuit() && parts->getRightHand()->isPursuit())) {
                co_yield{};
            }
            constexpr bool slowStart = true;
            if (isReverse) {
                parts->getLeftHand()->tryPursuit(Hand::HandDesc::CreateLeftPhase1(), slowStart);
                parts->getRightHand()->tryPursuit(Hand::HandDesc::CreateRightPhase1(), slowStart);
            } else {
                parts->getLeftHand()->tryPursuit(Hand::HandDesc::CreateLeftPhase2(), slowStart);
                parts->getRightHand()->tryPursuit(Hand::HandDesc::CreateRightPhase2(), slowStart);
            }

            // 待機
            co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase3::WaitInitAttack);

            // 二回手攻撃
            for ([[maybe_unused]]int32 count : step(2)) {
                // 右手攻撃
                parts->getRightHand()->tryAttack();

                // 待機
                co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase3::WaitAttack);

                // 左手攻撃
                parts->getLeftHand()->tryAttack();

                // 待機
                co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase3::WaitAttack);

                // 右手攻撃
                parts->getRightHand()->tryAttack();

                // 待機
                co_await BehaviorUtil::WaitForSeconds(pActor, Param::Phase3::WaitRestart);
            }
        }
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
