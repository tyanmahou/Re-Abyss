#include <abyss/components/Actor/Enemy/CodeZero/State/ShotState.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/State/WaitState.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/Builder.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/ShotProxy.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    void ShotState::start()
    {
        m_wing->startShot();
    }
    void ShotState::end()
    {
    }
    Coro::Fiber<> ShotState::updateAsync()
    {
        // チャージ開始
        m_parts->getRightHand()->tryShotCharge();
        m_parts->getLeftHand()->tryShotCharge();

        // 待機
        co_await BehaviorUtil::WaitForSeconds(m_pActor, Param::Phase3::WaitShot);

        // ショット生成
        auto shot = m_pActor->getModule<Actors>()->create<Shot::Builder>(m_pActor)
            ->find<Shot::ShotProxy>();

        // 待機
        co_await Coro::FiberUtil::WaitWhile([&] {
            return shot && !shot->isStartedPursuit();
        });

        this->changeState<WaitState>();
    }
    void ShotState::update()
    {
    }
}
