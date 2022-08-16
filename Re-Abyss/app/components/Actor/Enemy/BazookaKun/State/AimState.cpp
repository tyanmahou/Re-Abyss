#include <abyss/components/Actor/Enemy/BazookaKun/State/AimState.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    void AimState::start()
    {
    }

    Task<> AimState::task()
    {
        // バズーカ登場
        TimeLite::Timer timer{ 0.65 };
        while (!timer.isEnd()) {
            timer.update(m_pActor->deltaTime());
            m_motion->setAnimeTime(timer.rate());
            co_yield{};
        }
        // 少し待つ
        co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.25);

        // エイム開始
        m_target->setIsValidAim(true);
        co_return;
    }
}
