#include <abyss/components/Actor/Enemy/BazookaKun/State/AimState.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>

#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/Shot/Builder.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    void AimState::start()
    {
    }

    void AimState::update()
    {
    }

    Fiber<> AimState::task()
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

        while (true) {
            if (m_target->isInAimRangeWithDist()) {
                m_pActor->getModule<World>()->create<Shot::Builder>(
                    m_target->bazookaPos(),
                    m_target->bazookaVec()
                    );
                co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.7);
                m_pActor->getModule<World>()->create<Shot::Builder>(
                    m_target->bazookaPos(),
                    m_target->bazookaVec()
                    );
                // 少し待つ
                co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.0);
            }
            co_yield{};
        }
        co_return;
    }
}
