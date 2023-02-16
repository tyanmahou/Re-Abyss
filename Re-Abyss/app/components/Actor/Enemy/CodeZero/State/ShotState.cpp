#include <abyss/components/Actor/Enemy/CodeZero/State/ShotState.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/State/WaitState.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/Builder.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    void ShotState::start()
    {
        m_wing->startShot();
    }
    void ShotState::end()
    {
    }
    Coro::Fiber<> ShotState::task()
    {
        // チャージ開始
        m_parts->getRightHand()->tryShotCharge();
        m_parts->getLeftHand()->tryShotCharge();

        // 待機
        co_await BehaviorUtil::WaitForSeconds(m_pActor, Param::Phase3::WaitShot);

        // ショット生成
        m_pActor->getModule<Actors>()->create<Shot::Builder>(m_pActor);

        // 待機
        co_await BehaviorUtil::WaitForSeconds(m_pActor, Param::Phase3::WaitPursuit);

        this->changeState<WaitState>();
    }
    void ShotState::update()
    {
    }
}
