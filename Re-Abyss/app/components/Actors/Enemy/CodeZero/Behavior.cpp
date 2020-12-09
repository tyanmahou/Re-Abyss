#include "Behavior.hpp"

#include <Siv3D.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Manager/Manager.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Shot/ShotActor.hpp>

#include <abyss/components/Actors/utils/BehaviorUtil.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/PartsCtrl.hpp>

#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Coro::Task<> Behavior::Petern1(IActor* pActor)
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

    Coro::Task<> Behavior::Petern2(IActor* pActor)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        // 追従開始
        parts->getLeftHand()->tryPursuit();
        parts->getRightHand()->tryPursuit();

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

    Coro::Task<> Behavior::Petern3(IActor* pActor)
    {
        auto parts = pActor->find<PartsCtrl>().get();

        // 1ループ目だけ長め
        double waitShotSec = Param::Phase3::WaitPursuit;
        while (true) {

            // チャージ開始
            parts->getRightHand()->tryShotCharge();
            parts->getLeftHand()->tryShotCharge();

            // 待機
            co_yield BehaviorUtils::WaitForSeconds(pActor, waitShotSec);
            waitShotSec = Param::Phase3::WaitShot;

            // ショット生成
            pActor->getModule<World>()->create<Shot::ShotActor>(pActor);

            // 待機
            co_yield BehaviorUtils::WaitForSeconds(pActor, Param::Phase3::WaitPursuit);

            // 追従開始
            parts->getLeftHand()->tryPursuit();
            parts->getRightHand()->tryPursuit();

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
