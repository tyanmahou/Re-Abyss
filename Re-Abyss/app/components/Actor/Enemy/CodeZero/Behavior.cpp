#include "Behavior.hpp"

#include <Siv3D.hpp>

#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Manager/Manager.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/Builder.hpp>

#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>

#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Coro::Task<> Behavior::Petern1(ActorObj* pActor)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        // 待機
        co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase1::WaitRestart);

        while (true) {
            // 左手攻撃
            parts->getLeftHand()->tryAttack();

            // 待機
            co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase1::WaitAttack);

            // 右手攻撃
            parts->getRightHand()->tryAttack();

            // 待機
            co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase2::WaitRestart);
        }
        co_return;
    }

    Coro::Task<> Behavior::Petern2(ActorObj* pActor)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        // 追従開始
        parts->getLeftHand()->tryPursuit(Hand::HandDesc::CreateLeftPhase2());
        parts->getRightHand()->tryPursuit(Hand::HandDesc::CreateRightPhase2());

        // 待機
        co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase2::WaitInit);

        while (true) {
            // 右手攻撃
            parts->getRightHand()->tryAttack();

            // 待機
            co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase2::WaitAttack);

            // 左手攻撃
            parts->getLeftHand()->tryAttack();

            // 待機
            co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase2::WaitDualAttack);

            // 両手攻撃
            parts->getRightHand()->tryAttack();
            parts->getLeftHand()->tryAttack();

            // 待機
            co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase2::WaitRestart);
        }
        co_return;
    }

    Coro::Task<> Behavior::Petern3(ActorObj* pActor)
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
            co_yield BehaviorUtils::WaitForSeconds(pActor, waitShotSec);
            waitShotSec = Param::Phase3::WaitShot;

            // ショット生成
            pActor->getModule<World>()->create<Shot::Builder>(pActor);

            // 待機
            co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase3::WaitPursuit);

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
            co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase3::WaitInitAttack);

            // 二回手攻撃
            for ([[maybe_unused]]int32 count : step(2)) {
                // 右手攻撃
                parts->getRightHand()->tryAttack();

                // 待機
                co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase3::WaitAttack);

                // 左手攻撃
                parts->getLeftHand()->tryAttack();

                // 待機
                co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase3::WaitAttack);

                // 右手攻撃
                parts->getRightHand()->tryAttack();

                // 待機
                co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase3::WaitRestart);
            }
        }
        co_return;
    }

}
